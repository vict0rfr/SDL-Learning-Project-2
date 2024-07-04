#include "player.h"
#include "graphics.h"

namespace player_constants{
    const float WALK_SPEED = 0.2f;
    const float GRAVITY = 0.002f;
    const float GRAVITY_CAP = 0.8f;
}

Player::Player(){}

Player::Player(Graphics &p_graphics, Vector2f p_spawnPoint):
    AnimatedSprite(p_graphics, "../res/gfx/MyChar.png", 0, 0, 16, 16, p_spawnPoint.x, p_spawnPoint.y, 100),
        _dx(0),
        _dy(0),
        _facing(RIGHT),
        _grounded(false)
    {
        p_graphics.loadImage("../res/gfx/MyChar.png");
        this->setupAnimations();
        this->playAnimation("RunRight");
    }

void Player::draw(Graphics &p_graphics){
    AnimatedSprite::draw(p_graphics, this->_x, this ->_y);
}

void Player::moveLeft(){
    this->_dx = -player_constants::WALK_SPEED;
    this->playAnimation("RunLeft");
    this->_facing = LEFT;
}

void Player::moveRight(){
    this->_dx = player_constants::WALK_SPEED;
    this->playAnimation("RunRight");
    this->_facing = RIGHT;
}

void Player::stopMoving(){
    this->_dx = 0.0f;
    this->playAnimation(this->_facing == RIGHT ? "IdleRight" : "IdleLeft");
}

void Player::update(float p_elapsedTime){
    //Apply gravity
    if(this->_dy <= player_constants::GRAVITY_CAP){
        this->_dy += player_constants::GRAVITY * p_elapsedTime;
    }

    this->_x += _dx * p_elapsedTime;
    this->_y += _dy * p_elapsedTime;
    AnimatedSprite::update(p_elapsedTime);
}

void Player::animationDone(std::string p_currentAnimation){

}

void Player::setupAnimations(){
    this->addAnimation(1, 0, 0, "IdleLeft", 16, 16, Vector2f(0, 0));
    this->addAnimation(1, 0, 16, "IdleRight", 16, 16, Vector2f(0, 0));
    this->addAnimation(3, 0, 0, "RunLeft", 16, 16, Vector2f(0, 0));
    this->addAnimation(3, 0, 16, "RunRight", 16, 16, Vector2f(0, 0));
}

void Player::handleTileCollisions(std::vector<Rectangle> &p_others){
    //figure out the side the collision was and move accordingly
    for(int i = 0; i < p_others.size(); i++){
        sides::Side collisionSide = getCollisionSide(p_others.at(i));
            switch(collisionSide){
                case sides::TOP:
                    this->_y = p_others.at(i).getBottom() + 1;
                    this->_dy = 0;
                    break;
                case sides::BOTTOM:
                    this->_y = p_others.at(i).getTop() - this->_boundingBox.getHeight() - 1;
                    this->_dy = 0;
                    this->_grounded = true;
                    break;
                case sides::LEFT:
                    this->_x = p_others.at(i).getRight() + 1;
                    break;
                case sides::RIGHT:
                    this->_x = p_others.at(i).getLeft() - this->_boundingBox.getWidth() - 1;
                    break;
                case sides::NONE:
                    continue;
            }
    }
}

float Player::getX() const{
    return this->_x;
}

float Player::getY() const{
    return this->_y;
}