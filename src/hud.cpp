#include "hud.h"
#include "graphics.h"
#include <iostream>

Hud::Hud(){}

Hud::Hud(Graphics &p_graphics, Player &p_player){
    this->_player = p_player;
    this->_healthBarSprite = Sprite(p_graphics, "../res/gfx/TextBox.png", 0, 40, 64, 8, 35, 70);
    this->_healthNumber1 = Sprite(p_graphics, "../res/gfx/TextBox.png", 0, 56, 8, 8, 66, 70);
    this->_currentHealthBar = Sprite(p_graphics, "../res/gfx/TextBox.png", 0, 25, 39, 5, 83, 72);
    this->_lvWord = Sprite(p_graphics, "../res/gfx/TextBox.png", 81, 81, 11, 7, 38, 55);
    this->_lvNumber = Sprite(p_graphics, "../res/gfx/TextBox.png", 0, 56, 8, 8, 66, 52);
    this->_expBar = Sprite(p_graphics, "../res/gfx/TextBox.png", 0, 72, 40, 8, 83, 52);
    this->_slash = Sprite(p_graphics, "../res/gfx/TextBox.png", 72, 48, 8, 8, 100, 36);
    this->_dashes = Sprite(p_graphics, "../res/gfx/TextBox.png", 81, 51, 15, 11, 132, 26);
}

void Hud::update(int p_elapsedTime, Player &p_player){
    this->_player = p_player;
    this->_healthNumber1.setSourceRectX(8 * this->_player.getCurrentHealth());

    //calculate the width of the health bar
    float num = (float)this->_player.getCurrentHealth() / this->_player.getMaxHealth();
    this->_currentHealthBar.setSourceRectW(std::floor(num * 39));
}

void Hud::draw(Graphics &p_graphics){
    this->_healthBarSprite.draw(p_graphics, this->_healthBarSprite.getX(), this->_healthBarSprite.getY());
    this->_healthNumber1.draw(p_graphics, this->_healthNumber1.getX(), this->_healthNumber1.getY());
    this->_currentHealthBar.draw(p_graphics, this->_currentHealthBar.getX(), this->_currentHealthBar.getY());
    this->_lvWord.draw(p_graphics, this->_lvWord.getX(), this->_lvWord.getY());
    this->_lvNumber.draw(p_graphics, this->_lvNumber.getX(), this->_lvNumber.getY());
    this->_expBar.draw(p_graphics, this->_expBar.getX(), this->_expBar.getY());
    this->_slash.draw(p_graphics, this->_slash.getX(), this->_slash.getY());
    this->_dashes.draw(p_graphics, this->_dashes.getX(), this->_dashes.getY());
    //use a for loop each, will hbave to make a vector that stores all sprites* and foreach loop thru them
}