#include <SDL2/SDL.h>
#include <sstream>
#include <algorithm>
#include <cmath>
#include <iostream>

#include "level.h"
#include "graphics.h"
#include "tinyxml2.h"
#include "utils.h"
#include "animatedTile.h"

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
    for(int i = 0; i < this->_animatedTileList.size(); i++){
        this->_animatedTileList[i].update(p_elapsedTime);
    }
}

void Level::draw(Graphics &p_graphics){
    for(int i = 0; i < this->_tileList.size(); i++){
        this->_tileList[i].draw(p_graphics);
    }

    for(int i = 0; i < this->_animatedTileList.size(); i++){
        this->_animatedTileList[i].draw(p_graphics);
    }
}

std::vector<Rectangle> Level::checkTileCollisions(const Rectangle &p_other){
    std::vector<Rectangle> others;
    for(int i = 0; i < this->_collisionRects.size(); i++){
        if(this->_collisionRects[i].collidesWith(p_other)){
            others.push_back(this->_collisionRects[i]);
        }
    }
    return others;
}


std::vector<Slope> Level::checkSlopeCollisions(const Rectangle &p_other){
    std::vector<Slope> others;
    for(int i = 0; i < this->_slopes.size(); i++){
        if(this->_slopes.at(i).collidesWith(p_other)){
            others.push_back(this->_slopes[i]);
        }
    }
    return others;
}

const Vector2f Level::getPlayerSpawnPoint() const {
    return this->_spawnPoint;
}

Vector2f Level::getTilesetPosition(Tileset p_tls, int p_gid, int p_tileWidth, int p_tileHeight){
    int tilesetWidth, tilesetHeight;
    SDL_QueryTexture(p_tls.Texture, NULL, NULL, &tilesetWidth, &tilesetHeight);
    int tsxx = p_gid % (tilesetWidth / p_tileWidth) - 1;
    tsxx *= p_tileWidth;
    int tsyy = 0;
    int amt = ((p_gid - p_tls.FirstGid) / (tilesetWidth / p_tileWidth));
    tsyy = p_tileHeight * amt;
    Vector2f finalTileSetPos = Vector2f(tsxx, tsyy);
    
    return finalTileSetPos;
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
            
            //get all the animations for that tileset before moving on
            XMLElement * pTileA = pTileset->FirstChildElement("tile");
            if(pTileA != NULL){
                while(pTileA){
                    AnimatedTileInfo ati;
                    ati.StartTileId = pTileA->IntAttribute("id") + firstGid;
                    ati.TilesetsFirstGid = firstGid;

                    XMLElement* pAnimation = pTileA->FirstChildElement("animation");
                    if(pAnimation != NULL){
                        while(pAnimation){
                            XMLElement* pFrame = pAnimation->FirstChildElement("frame");
                            if(pFrame != NULL){
                                while(pFrame){
                                    ati.TileIds.push_back(pFrame->IntAttribute("tileid") + firstGid);
                                    ati.Duration = pFrame->IntAttribute("duration");

                                    pFrame = pFrame->NextSiblingElement("frame");
                                }
                            }
                            this->_animatedTileInfo.push_back(ati);
                            pAnimation = pAnimation->NextSiblingElement("tile");
                        }
                    }
                    pTileA = pTileA->NextSiblingElement("tile");
                }
            }
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
                            int closest = 0;
                            for(int i = 0; i < this->_tilesets.size(); i++){
                                if(this->_tilesets[i].FirstGid <= gid){
                                    if(this->_tilesets[i].FirstGid > closest){
                                        closest = this->_tilesets[i].FirstGid;
                                        tls = this->_tilesets[i];
                                    }
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
                            Vector2f finalTileSetPos = this->getTilesetPosition(tls, gid, tileWidth, tileHeight);

                            //build the tile and add it to the level's tile list
                            bool isAnimatedTile = false;
                            AnimatedTileInfo ati;

                            for(int i = 0; i < this->_animatedTileInfo.size(); i++){
                                if(this->_animatedTileInfo[i].StartTileId == gid){
                                    ati = this->_animatedTileInfo[i];
                                    isAnimatedTile = true;
                                    break;
                                }
                            }

                            if(isAnimatedTile){
                                std::vector<Vector2f> tilesetPositions;
                                for(int i = 0; i < ati.TileIds.size(); i++){
                                    tilesetPositions.push_back(this->getTilesetPosition(tls, ati.TileIds[i],
                                        tileWidth, tileHeight));
                                } // moved this out of the for loop
                                AnimatedTile tile(tilesetPositions, ati.Duration, tls.Texture,
                                    Vector2f(tileWidth, tileHeight), finalTilePos);
                                this->_animatedTileList.push_back(tile);
                            } else {
                            Tile tile(tls.Texture, Vector2f(tileWidth, tileHeight),
                                finalTileSetPos, finalTilePos);
                            this->_tileList.push_back(tile);
                            }
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
            } else if(ss.str() == "slopes"){
                XMLElement* pObject = pObjectGroup->FirstChildElement("object");
                if(pObject != NULL){
                    while(pObject){
                        std::vector<Vector2f> points;
                        Vector2f p1;
                        p1 = Vector2f(std::ceil(pObject->FloatAttribute("x")), std::ceil(pObject->FloatAttribute("y")));

                        XMLElement* pPolyline = pObject->FirstChildElement("polyline");
                        if(pPolyline != NULL){
                            std::vector<std::string> pairs;
                            const char* pointString = pPolyline->Attribute("points");

                            std::stringstream ss;
                            ss << pointString;

                            Utils::split(ss.str(), pairs, ' ');

                            for(int i = 0; i < pairs.size(); i++){
                                std::vector<std::string> ps;
                                Utils::split(pairs.at(i), ps, ',');
                                points.push_back(Vector2f(std::stoi(ps.at(0)), std::stoi(ps.at(1))));
                            }
                        }

                        for(int i = 0; i < points.size(); i+= 2){
                            this->_slopes.push_back(Slope(
                                Vector2f((p1.x + points.at(i < 2 ? i : i - 1).x) * globals::SPRITE_SCALE,
                                        (p1.y + points.at(i < 2 ? i : i - 1).y) * globals::SPRITE_SCALE),
                                Vector2f((p1.x + points.at(i < 2 ? i + 1 : i).x) * globals::SPRITE_SCALE,
                                        (p1.y + points.at(i < 2 ? i + 1 : i).y) * globals::SPRITE_SCALE)
                                ));
                        }
                        pObject = pObject->NextSiblingElement("object");
                    }
                } 
            } else if(ss.str() == "spawn points"){
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