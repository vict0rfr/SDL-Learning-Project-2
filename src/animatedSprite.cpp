#include "animatedSprite.h"
#include "graphics.h"
#include "sprite.h"

#include <string>

AnimatedSprite::AnimatedSprite(){}

AnimatedSprite::AnimatedSprite(Graphics &p_graphics, const std::string &p_filePath, int p_sourceX, 
           int p_sourceY, int p_width, int p_height, float p_posX,
           float p_posY, float p_timeToUpdate):
              Sprite(p_graphics, p_filePath, p_sourceX, p_sourceY, p_width, p_height, p_posX, p_posY),
                _frameIndex(0),
                _timeElapsed(0),
                _timeToUpdate(p_timeToUpdate),
                _visible(true),
                _currentAnimationOnce(false),
                _currentAnimation("")
           {

           }

void AnimatedSprite::playAnimation(std::string p_animation, bool p_once){
    this->_currentAnimationOnce = p_once;
    if(this->_currentAnimation != p_animation){
        this->_currentAnimation = p_animation;
        this->_frameIndex = 0;
    }
}

void AnimatedSprite::update(int p_elapsedTime){
    Sprite::update();

    this->_timeElapsed += p_elapsedTime;
    if(this->_timeElapsed >= this->_timeToUpdate){
        this->_timeElapsed -= this->_timeToUpdate;
        if(this->_frameIndex < this->_animations[this->_currentAnimation].size() - 1){
            this->_frameIndex++;
        } else {
            if(this->_currentAnimationOnce == true){
                this->setVisible(false);
            }
            this->stopAnimation();
        }
    }
}

void AnimatedSprite::draw(Graphics &p_graphics, int p_x, int p_y){
    if(this->_visible){
        SDL_Rect dst;
        dst.x = p_x + this->_offests[this->_currentAnimation].x;
        dst.y = p_y + this->_offests[this->_currentAnimation].y;
        dst.w = this->_src.w * globals::SPRITE_SCALE;
        dst.h = this->_src.h * globals::SPRITE_SCALE;

        SDL_Rect src = this->_animations[this->_currentAnimation][this->_frameIndex];
        p_graphics.blitSurface(this->_spriteSheet, &src, &dst);
    }
}

void AnimatedSprite::addAnimation(int p_frames, int p_x, int p_y, std::string p_name, int p_width, int p_height, Vector2f p_offset){
    std::vector<SDL_Rect> rectangles;
    for(int i = 0; i < p_frames; i++){
        SDL_Rect newRect = { (i + p_x) * p_width, p_y, p_width, p_height};
        rectangles.push_back(newRect);
    }

    this->_animations.insert(std::pair<std::string, std::vector<SDL_Rect> > (p_name, rectangles));
    this->_offests.insert(std::pair<std::string, Vector2f> (p_name, p_offset));
}

void AnimatedSprite::resetAnimations(){
    this->_animations.clear();
    this->_offests.clear();
}

void AnimatedSprite::stopAnimation(){
    this->_frameIndex = 0;
    this->animationDone(this->_currentAnimation);
}

void AnimatedSprite::setVisible(bool p_visible){
    this->_visible = p_visible;
}

void AnimatedSprite::animationDone(std::string p_currentAnimation){

}