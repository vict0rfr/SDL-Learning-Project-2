#include "graphics.h"
#include "animatedTile.h"
#include <SDL2/SDL_rect.h>

AnimatedTile::AnimatedTile(std::vector<Vector2f> p_tilesetPositions, int p_duration, 
    SDL_Texture* p_tileset, Vector2f p_size, Vector2f p_position):
    Tile(p_tileset, p_size, p_tilesetPositions[0], p_position),
    _tilesetPositions(p_tilesetPositions),
    _duration(p_duration),
    _tileToDraw(0)
{
}

void AnimatedTile::update(int p_elapsedTime){
    if(this->_amountOfTime <= 0){
        if(this->_tileToDraw == this->_tilesetPositions.size() - 1){
            this->_tileToDraw = 0;
        }else{
            this->_tileToDraw++;
        }
        this->_amountOfTime = this->_duration;
    } else{
        this->_amountOfTime -= p_elapsedTime;
    }
    Tile::update(p_elapsedTime);
}

void AnimatedTile::draw(Graphics &p_graphics){
    SDL_Rect src = {this->_tilesetPositions[this->_tileToDraw].x, this->_tilesetPositions[this->_tileToDraw].y, 
    this->_size.x, this->_size.y};

    SDL_Rect dst = {this->_position.x, this->_position.y, 
    this->_size.x * globals::SPRITE_SCALE, this->_size.y * globals::SPRITE_SCALE};
    
    p_graphics.blitSurface(this->_tileset, &src, &dst);
}