#include "player.h"
#include "graphics.h"

#include <iostream>

namespace player_constants{
    const float WALK_SPEED = 0.2f;
    const float GRAVITY = 0.002f;
    const float GRAVITY_CAP = 0.8f;
    const float JUMP_SPEED = 0.7f;
}

Player::Player(){}

Player::Player(Graphics &p_graphics, Vector2f p_spawnPoint):
    AnimatedSprite(p_graphics, "../res/gfx/MyChar.png", 0, 0, 16, 16, p_spawnPoint.x, p_spawnPoint.y, 100),
        _dx(0),
        _dy(0),
        _facing(RIGHT),
        _grounded(false),
        _lookingUp(false),
        _lookingDown(false),
        _maxHealth(3),
        _currentHealth(3)
    {
        p_graphics.loadImage("../res/gfx/MyChar.png");
        this->setupAnimations();
        this->playAnimation("IdleRight");
    }

void Player::draw(Graphics &p_graphics){
    AnimatedSprite::draw(p_graphics, this->_x, this ->_y);
}

void Player::moveLeft(){
    if(this->_lookingDown && this->_grounded){
        return;
    }

    this->_dx = -player_constants::WALK_SPEED;

    if(this->_lookingUp == false){
        this->playAnimation("RunLeft");
    }
    this->_facing = LEFT;
}

void Player::moveRight(){
    if(this->_lookingDown && this->_grounded){
        return;
    }
    this->_dx = player_constants::WALK_SPEED;

    if(this->_lookingUp == false){
        this->playAnimation("RunRight");
    }
    this->_facing = RIGHT;
}

void Player::lookUp(){
    this->_lookingUp = true;

    if(this->_dx == 0){
        this->playAnimation(this->_facing == RIGHT ? "IdleRightUp" : "IdleLeftUp");
    } else {
        this->playAnimation(this->_facing == RIGHT ? "RunRightUp" : "RunLeftUp");
    }
}

void Player::stopLookingUp(){
    this->_lookingUp = false;
}

void Player::lookDown(){
    this->_lookingDown = true;
    if(this->_grounded){
        this->playAnimation(this->_facing == RIGHT ? "LookBackwardsRight" : "LookBackwardsLeft");
        this->_dx = 0.0f; // without this, it makes it possible to move while looking down, which looks weird
    } else {
        this->playAnimation(this->_facing == RIGHT ? "LookDownRight" : "LookDownLeft");
    }
}

void Player::stopLookingDown(){
    this->_lookingDown = false;
}

void Player::stopMoving(){
    this->_dx = 0.0f;

    if(this->_lookingUp == false && this->_lookingDown == false){
        this->playAnimation(this->_facing == RIGHT ? "IdleRight" : "IdleLeft");
    }
}

void Player::jump(){
    if(this->_grounded){
        this->_dy = 0;
        this->_dy -= player_constants::JUMP_SPEED;
        this->_grounded = false;
    }
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

void Player::setupAnimations() {
	this->addAnimation(1, 0, 0, "IdleLeft", 16, 16, Vector2f(0,0));
	this->addAnimation(1, 0, 16, "IdleRight", 16, 16, Vector2f(0,0));
	this->addAnimation(3, 0, 0, "RunLeft", 16, 16, Vector2f(0,0));
	this->addAnimation(3, 0, 16, "RunRight", 16, 16, Vector2f(0,0));
	this->addAnimation(1, 3, 0, "IdleLeftUp", 16, 16, Vector2f(0,0));
	this->addAnimation(1, 3, 16, "IdleRightUp", 16, 16, Vector2f(0,0));
	this->addAnimation(3, 3, 0, "RunLeftUp", 16, 16, Vector2f(0,0));
	this->addAnimation(3, 3, 16, "RunRightUp", 16, 16, Vector2f(0,0));
	this->addAnimation(1, 6, 0, "LookDownLeft", 16, 16, Vector2f(0,0));
	this->addAnimation(1, 6, 16, "LookDownRight", 16, 16, Vector2f(0,0));
	this->addAnimation(1, 7, 0, "LookBackwardsLeft", 16, 16, Vector2f(0,0));
	this->addAnimation(1, 7, 16, "LookBackwardsRight", 16, 16, Vector2f(0,0));
}

void Player::handleTileCollisions(std::vector<Rectangle> &p_others){
    //figure out the side the collision was and move accordingly
    for(int i = 0; i < p_others.size(); i++){
        sides::Side collisionSide = getCollisionSide(p_others.at(i));
            switch(collisionSide){
                case sides::TOP:
                    this->_dy = 0;
                    this->_y = p_others.at(i).getBottom() + 1;
                    if(this->_grounded){
                        this->_dx = 0;
                        this->_x -= this->_facing == RIGHT ? 1.0f : -1.0f;
                    }
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
                default:
                    break;
            }
    }
}

void Player::handleSlopeCollisions(std::vector<Slope> &p_others){
    for(int i = 0; i < p_others.size(); i++){
        int b = (p_others.at(i).getP1().y - (p_others.at(i).getSlope() * p_others.at(i).getP1().x));

        int centerX = this->_boundingBox.getCenterX();
        int newY = (p_others.at(i).getSlope() * centerX) + b - 8;

        if(this->_grounded){
            this->_y = newY - this->_boundingBox.getHeight();
            this->_grounded = true;
        }
    }
}

void Player::handleDoorCollision(std::vector<Door> &p_others, Level &p_level, Graphics &p_graphics){
    for(int i = 0; i < p_others.size(); i++){
        if(this->_grounded && this->_lookingDown){
            p_level = Level(p_others.at(i).getDestination(), p_graphics);
            this->_x = p_level.getPlayerSpawnPoint().x;
            this->_y = p_level.getPlayerSpawnPoint().y;
        }
    }
}

float Player::getX() const{
    return this->_x;
}

float Player::getY() const{
    return this->_y;
}