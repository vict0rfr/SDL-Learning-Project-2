#include "hud.h"
#include "graphics.h"

Hud::Hud(){}

Hud::Hud(Graphics &p_graphics, Player &p_player){
    this->_player = p_player;
    this->_healthBarSprite = Sprite(p_graphics, "../res/gfx/TextBox.png", 0, 40, 64, 8, 35, 70);
    this->_healthNumber1 = Sprite(p_graphics, "../res/gfx/TextBox.png", 0, 56, 8, 8, 66, 70);
}

void Hud::update(int p_elapsedTime){
    this->_healthNumber1.setSourceRectX(8 * this->_player.getCurrentHealth());
}

void Hud::draw(Graphics &p_graphics){
    this->_healthBarSprite.draw(p_graphics, this->_healthBarSprite.getX(), this->_healthBarSprite.getY());
    this->_healthNumber1.draw(p_graphics, this->_healthNumber1.getX(), this->_healthNumber1.getY());
}