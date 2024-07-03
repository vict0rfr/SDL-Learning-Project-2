#include <SDL2/SDL.h>
#include <sstream>
#include <algorithm>
#include <cmath>

#include "level.h"
#include "graphics.h"
#include "tinyxml2.h"

using namespace tinyxml2;

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
            dst.w = 64 * globals::SPRITE_SCALE;
            dst.h = 64 * globals::SPRITE_SCALE;
            p_graphics.blitSurface(this->_backgroundTexture, &src, &dst);
        }
    }
}

void Level::loadMap(std::string p_mapName, Graphics &p_graphics){
    //Parse the XML file
    XMLDocument doc;
    std::stringstream ss;
    ss << "../res/maps/" << p_mapName << ".tmx";
    doc.LoadFile(ss.str().c_str());

    XMLElement* mapNode = doc.FirstChildElement("map");

    //Get the w,h of the whole map and store it in _size
    int width, height;
    mapNode->QueryIntAttribute("width", &width);
    mapNode->QueryIntAttribute("height", &height);
    this->_size = Vector2f(width, height);

    //Get the w,h of the tiles and store it in _tileSize
    int tileWidth, tileHeight;
    mapNode->QueryIntAttribute("tilewidth", &tileWidth);
    mapNode->QueryIntAttribute("tileheight", &tileHeight);
    this->_tileSize = Vector2f(tileWidth, tileHeight);

    //Loading the tilesets for the map
    XMLElement* pTileset = mapNode->FirstChildElement("tileset");
    if(pTileset != NULL){
        while(pTileset){
            int firstGid;
            const char* source = pTileset->FirstChildElement("image")->Attribute("source");
            char* path;
            std::stringstream ss;
            ss << "../res/gfx/tilesets/" << source;
            pTileset->QueryIntAttribute("firstgid", &firstGid);
            SDL_Texture* tex = SDL_CreateTextureFromSurface(p_graphics.getRenderer(), p_graphics.loadImage(ss.str()));
            this->_tilesets.push_back(Tileset(tex, firstGid));
            
            pTileset = pTileset->NextSiblingElement("tileset");
        }
    }

    //Load the layers
    XMLElement* pLayer = mapNode->FirstChildElement("layer");
    if(pLayer != NULL){
        while(pLayer){

            pLayer = pLayer->NextSiblingElement("layer");
        }
    }
}