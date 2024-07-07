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

    this->_boundingBox = Rectangle(this->_x, this->_y, p_width * globals::SPRITE_SCALE, p_height * globals::SPRITE_SCALE);

}

Sprite::~Sprite(){

}

void Sprite::update(){
    this->_boundingBox = Rectangle(this->_x, this->_y, this->_src.w * globals::SPRITE_SCALE, this->_src.h * globals::SPRITE_SCALE);
}

void Sprite::draw(Graphics &p_graphics, int p_x, int p_y){
    SDL_Rect dst = {p_x, p_y, static_cast<int>(this->_src.w * globals::SPRITE_SCALE), 
    static_cast<int>(this->_src.h * globals::SPRITE_SCALE)};
    p_graphics.blitSurface(this->_spriteSheet, &this->_src, &dst);
}

const Rectangle Sprite::getBoundingBox() const{
    return this->_boundingBox;
}

const sides::Side Sprite::getCollisionSide(Rectangle &p_other) const{
    int amtRight, amtLeft, amtTop, amtBottom;

    amtRight = this->_boundingBox.getRight() - p_other.getLeft();
    amtLeft = p_other.getRight() - this->_boundingBox.getLeft();
    amtTop = p_other.getBottom() - this->_boundingBox.getTop();
    amtBottom = this->_boundingBox.getBottom() - p_other.getTop();

    int vals[4] = {abs(amtRight), abs(amtLeft), abs(amtTop), abs(amtBottom)};
    int lowest = vals[0];
    for(int i = 0; i < sizeof(vals) / sizeof(vals[0]); i++){
        if(vals[i] < lowest){
            lowest = vals[i];
        }
    }

    return
            lowest == abs(amtRight) ? sides::RIGHT :
            lowest == abs(amtLeft) ? sides::LEFT :
            lowest == abs(amtTop) ? sides::TOP :
            lowest == abs(amtBottom) ? sides::BOTTOM :
            sides::NONE;
}

void Sprite::setSourceRectX(int p_value){
    this->_src.x = p_value;
}

void Sprite::setSourceRectY(int p_value){
    this->_src.y = p_value;
}