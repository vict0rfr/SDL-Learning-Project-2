#include <SDL2/SDL.h>
#include <sstream>
#include <algorithm>
#include <cmath>
#include <iostream>

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
    for(int i = 0; i < this->_tileList.size(); i++){
        this->_tileList.at(i).draw(p_graphics);
    }
}

std::vector<Rectangle> Level::checkTileCollisions(const Rectangle &p_other){
    std::vector<Rectangle> others;
    for(int i = 0; i < this->_collisionRects.size(); i++){
        if(this->_collisionRects.at(i).collidesWith(p_other)){
            others.push_back(this->_collisionRects.at(i));
        }
    }
    return others;
}

const Vector2f Level::getPlayerSpawnPoint() const {
    return this->_spawnPoint;
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
            ss << source;
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
            //Loading data element
            XMLElement* pData = pLayer->FirstChildElement("data");
            if(pData != NULL){
                while(pData){
                    //Loading tile element
                    XMLElement* pTile = pData->FirstChildElement("tile");
                    if(pTile != NULL){
                        int tileCounter = 0;
                        while(pTile){
                            //build each tile here
                            //if gid is 0, there is no tile, continue
                             if(pTile->IntAttribute("gid") == 0){
                                tileCounter++;
                                if(pTile->NextSiblingElement("tile")){
                                    pTile = pTile->NextSiblingElement("tile");
                                    continue;
                                } else {
                                    break; 
                                }
                             }

                            int gid = pTile->IntAttribute("gid");
                            Tileset tls;
                            for(int i = 0; i < this->_tilesets.size(); i++){
                                if(this->_tilesets[i].FirstGid <= gid){
                                    tls = this->_tilesets.at(i);
                                    break;
                                }
                            }
                            if(tls.FirstGid == -1){
                                tileCounter++;
                                if(pTile->NextSiblingElement("tile")){
                                    pTile = pTile->NextSiblingElement("tile");
                                    continue;
                                } else { // means were done
                                    break;
                                }
                            }
                            // get the position of the tile in the level
                            int xx = 0;
                            int yy = 0;

                            xx = tileCounter % width;
                            xx *= tileWidth;

                            yy += tileHeight * (tileCounter / width);

                            Vector2f finalTilePos = Vector2f(xx, yy);

                            //calculate the position of the tile in its tileset
                            int tilesetWidth, tilesetHeight;
                            SDL_QueryTexture(tls.Texture, NULL, NULL, &tilesetWidth, &tilesetHeight);
                            int tsxx = gid % (tilesetWidth / tileWidth) - 1;
                            tsxx *= tileWidth;
                            int tsyy = 0;
                            int amt = (gid / (tilesetWidth / tileWidth));
                            tsyy = tileHeight * amt;
                            Vector2f finalTileSetPos = Vector2f(tsxx, tsyy);

                            //build the tile and add it to the level's tile list
                            Tile tile(tls.Texture, Vector2f(tileWidth, tileHeight),
                                finalTileSetPos, finalTilePos);
                            this->_tileList.push_back(tile);
                            tileCounter++;

                             pTile = pTile->NextSiblingElement("tile");
                        }
                    }


                    pData = pData->NextSiblingElement("data");
                }
            }
            
            pLayer = pLayer->NextSiblingElement("layer");
        }
    }

    //parse the collisions
    XMLElement* pObjectGroup = mapNode->FirstChildElement("objectgroup");
    if(pObjectGroup != NULL){
        while(pObjectGroup){
            const char* name = pObjectGroup->Attribute("name");
            std::stringstream ss;
            ss << name;
            if(ss.str() == "collisions"){
                XMLElement* pObject = pObjectGroup->FirstChildElement("object");
                if(pObject != NULL){
                    while(pObject){
                        float x, y, width, height;
                        x = pObject->FloatAttribute("x");
                        y = pObject->FloatAttribute("y");
                        width = pObject->FloatAttribute("width");
                        height = pObject->FloatAttribute("height");
                        this->_collisionRects.push_back(Rectangle(
                            std::ceil(x) * globals::SPRITE_SCALE,
                            std::ceil(y) * globals::SPRITE_SCALE,
                            std::ceil(width) * globals::SPRITE_SCALE,
                            std::ceil(height) * globals::SPRITE_SCALE
                        ));

                        pObject = pObject->NextSiblingElement("object");
                    }
                } 
            }
            else if(ss.str() == "spawn points"){
                XMLElement* pObject = pObjectGroup->FirstChildElement("object");
                if(pObject != NULL){
                    while(pObject){
                        float x = pObject->FloatAttribute("x");
                        float y = pObject->FloatAttribute("y");
                        const char* name = pObject->Attribute("name");
                        std::stringstream ss;
                        ss << name;
                        if(ss.str() == "player"){
                            this->_spawnPoint = Vector2f(std::ceil(x) * globals::SPRITE_SCALE, std::ceil(y) * globals::SPRITE_SCALE);
                        }

                        pObject = pObject->NextSiblingElement("object");
                    }
                }
            }
            pObjectGroup = pObjectGroup->NextSiblingElement("objectgroup");
        }
    }
}