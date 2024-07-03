#include <SDL2/SDL.h>

#include "tile.h"
#include "graphics.h"

Tile::Tile(){}

Tile::Tile(SDL_Texture* p_tileset, Vector2f p_size, Vector2f p_tilesetPosition, Vector2f p_position):
    _tileset(p_tileset),
    _size(p_size),
    _tilesetPosition(p_tilesetPosition),
    _position(Vector2f(p_position.x * globals::SPRITE_SCALE, p_position.y * globals::SPRITE_SCALE))
{

}

void Tile::update(int p_elapsedTime){

}

void Tile::draw(Graphics &p_graphics){
    SDL_Rect dst = {this->_position.x, this->_position.y, 
    this->_size.x * globals::SPRITE_SCALE, this->_size.y * globals::SPRITE_SCALE};
    SDL_Rect src = {this->_tilesetPosition.x, this->_tilesetPosition.y, 
    this->_size.x, this->_size.y};

    p_graphics.blitSurface(this->_tileset, &src, &dst);
}