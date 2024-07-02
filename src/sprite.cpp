#include "sprite.h"
#include "graphics.h"
#include "globals.h"

Sprite::Sprite(){}

Sprite::Sprite(Graphics &p_graphics, const std::string &p_filePath, int p_sourceX, 
int p_sourceY, int p_width, int p_height, float p_posX, float p_posY):
    _x(p_posX),
    _y(p_posY)
{
    this->_src.x = p_sourceX;
    this->_src.y = p_sourceY;
    this->_src.w = p_width;
    this->_src.h = p_height;

    this->_spriteSheet = SDL_CreateTextureFromSurface(p_graphics.getRenderer(), p_graphics.loadImage(p_filePath));
    if(this->_spriteSheet == NULL)
        printf("\nError: Unable to load image onto _spriteShett\n");
}

Sprite::~Sprite(){

}

void Sprite::update(){

}

void Sprite::draw(Graphics &p_graphics, int p_x, int p_y){
    SDL_Rect dst = {p_x, p_y, static_cast<int>(this->_src.w * globals::SPRITE_SCALE), 
    static_cast<int>(this->_src.h * globals::SPRITE_SCALE)};
    p_graphics.blitSurface(this->_spriteSheet, &this->_src, &dst);
}
