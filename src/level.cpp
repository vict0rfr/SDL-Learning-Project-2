#include <SDL2/SDL.h>

#include "level.h"
#include "graphics.h"

Level::Level(){}

Level::Level(std::string p_mapName, Vector2f p_spawnPoint, Graphics &p_graphics):
    _mapName(p_mapName),
    _spawnPoint(p_spawnPoint),
    _size(Vector2f(0,0))
{
    this->loadMap(p_mapName, p_graphics);
}

Level::~Level(){}

void Level::update(int p_elapsedTime){

}

void Level::draw(Graphics &p_graphics){
    SDL_Rect src = {0, 0, 64, 64};
    SDL_Rect dst;
    for(int x = 0; x < this->_size.x / 64; x++){
        for(int y = 0; y < this->_size.y / 64; y++){
            dst.x = x * 64 * globals::SPRITE_SCALE;
            dst.y = y * 64 * globals::SPRITE_SCALE;
            dst.w = 64;
            dst.h = 64;
            p_graphics.blitSurface(this->_backgroundTexture, &src, &dst);
        }
    }
}

void Level::loadMap(std::string p_mapName, Graphics &p_graphics){
    //TEMPORARY CODE
    this->_backgroundTexture = SDL_CreateTextureFromSurface(p_graphics.getRenderer(),
    p_graphics.loadImage("../res/gfx/background/bkBlue.png"));
    this->_size = Vector2f(1280, 960);
}