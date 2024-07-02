#include "player.h"
#include "graphics.h"

namespace player_constants{
    const float WALK_SPEED = 0.2f;
}


Player::Player(){}

Player::Player(Graphics &p_graphics, float p_x, float p_y):
    AnimatedSprite(p_graphics, "../res/gfx/MyChar.png", 0, 0, 16, 16, p_x, p_y, 100){
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
    this->_x += _dx * p_elapsedTime;
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