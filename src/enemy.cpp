#include "enemy.h"

Enemy::Enemy(){}

Enemy::Enemy(Graphics &p_graphics, std::string p_filePath, int p_sourceX, int p_sourceY,
    int p_width, int p_height, Vector2f p_spawnPoint, int p_timeToUpdate):
        AnimatedSprite(p_graphics, p_filePath, p_sourceX, p_sourceY, p_width, p_height,
            p_spawnPoint.x, p_spawnPoint.y, p_timeToUpdate),
            _direction(LEFT),
            _maxHealth(0),
            _currentHealth(0),
            _isInvicible(false),
            _invincibilityDuration(2000), // 2000ms
            _invincibilityTimer(0)
        {}

void Enemy::update(int p_elapsedTime, Player &p_player){
    // update invinc timer
    if(this->_isInvicible){
        this->_invincibilityTimer -= p_elapsedTime;
        if(this->_invincibilityTimer <= 0){
            this->_isInvicible = false;
        }
    }

    AnimatedSprite::update(p_elapsedTime);
}

void Enemy::draw(Graphics &p_graphics){
    AnimatedSprite::draw(p_graphics, this->_x, this->_y);
}

void Enemy::touchPlayer(Player* p_player){
    if(!this->_isInvicible){
            p_player->gainHealth(-1);
            this->_isInvicible = true;
            this->_invincibilityTimer = this->_invincibilityDuration; //sets the clock ticking 1sec
    }
}

Bat::Bat(){}

Bat::Bat(Graphics &p_graphics, Vector2f p_spawnPoint):
    Enemy(p_graphics, "../res/gfx/NpcCemet.png", 32, 32, 16, 16, p_spawnPoint, 140),
        _startingX(p_spawnPoint.x),
        _startingY(p_spawnPoint.y),
        _shouldMoveUp(false)
    {
        this->setupAnimations();
        this->playAnimation("FlyLeft");
    }

void Bat::update(int p_elapsedTime, Player &p_player){
    this->_direction = p_player.getX() > this->_x ? RIGHT : LEFT;
    this->playAnimation(this->_direction == RIGHT ? "FlyRight" : "FlyLeft");

    //move up or down
    this->_y += this->_shouldMoveUp ? -.005 : .005;
    if(this->_y > (this->_startingY + 20) || this->_y < this->_startingY - 20){
        this->_shouldMoveUp = !this->_shouldMoveUp;
    }

    Enemy::update(p_elapsedTime, p_player);
}

void Bat::draw(Graphics &p_graphics){
    Enemy::draw(p_graphics);
}

void Bat::touchPlayer(Player* p_player){
    Enemy::touchPlayer(p_player);
}

void Bat::animationDone(std::string p_currentAnimation){

}

void Bat::setupAnimations(){
    this->addAnimation(3, 2, 32, "FlyLeft", 16, 16, Vector2f(0, 0));
    this->addAnimation(3, 2, 48, "FlyRight", 16, 16, Vector2f(0, 0));
}