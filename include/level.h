/**
 * @file level.h
 * @brief Level class definition for managing game levels.
 * 
 * This file defines the Level class, which is responsible for loading, updating, and rendering levels in the game.
 * It includes functionality for managing the level's background texture and handling level-specific updates and drawing.
 */

#ifndef LEVEL
#define LEVEL

#include "globals.h"
#include "tile.h"
#include "rectangle.h"
#include "slope.h"
#include "animatedTile.h"

class Graphics;
struct SDL_Texture;
struct SDL_Rect;
struct Tileset;

#include <string>
#include <vector> 

/**
 * @class Level
 * @brief Manages game levels, including loading, updating, and rendering.
 * 
 * The Level class is responsible for the lifecycle of a game level, from loading the map and resources,
 * to updating level state, and rendering the level to the screen. It uses SDL_Texture to manage the level's
 * background texture.
 */
class Level{
    public:
        /**
         * @brief Default constructor. Initializes an empty level.
         */
        Level();

        /**
         * @brief Constructs a Level with a map name, spawn point, and graphics context.
         * 
         * @param p_mapName Name of the map file to load.
         * @param p_spawnPoint Initial spawn point within the level.
         * @param p_graphics Graphics context for rendering the level.
         */
        Level(std::string p_mapName, Vector2f p_spawnPoint, Graphics &p_graphics);

        /**
         * @brief Destructor. Cleans up resources used by the level.
         */
        ~Level();

        /**
         * @brief Updates the level state.
         * 
         * @param p_elapsedTime Time elapsed since the last update call.
         */
        void update(int p_elapsedTime);

        /**
         * @brief Draws the level to the screen.
         * 
         * @param p_graphics Graphics context used for rendering.
         */
        void draw(Graphics &p_graphics);

        std::vector<Rectangle> checkTileCollisions(const Rectangle &p_other);

        std::vector<Slope> checkSlopeCollisions(const Rectangle &p_other);

        const Vector2f getPlayerSpawnPoint() const;

    private:
        std::string _mapName; ///< Name of the map file for the level.

        Vector2f _spawnPoint; ///< Initial spawn point within the level.
        Vector2f _size; ///< Size of the level.
        Vector2f _tileSize; ///< Size of the tile.

        SDL_Texture* _backgroundTexture; ///< Texture for the level's background.

        std::vector<Tile> _tileList;
        std::vector<Tileset> _tilesets;
        std::vector<Rectangle> _collisionRects;
        std::vector<Slope> _slopes;

        std::vector<AnimatedTile> _animatedTileList;
        std::vector<AnimatedTileInfo> _animatedTileInfo;

        Vector2f getTilesetPosition(Tileset p_tls, int p_gid, int p_tileWidth, int p_tileHeight);
        /**
         * @brief Loads the map and resources for the level.
         * 
         * @param p_mapName Name of the map file to load.
         * @param p_graphics Graphics context used for loading textures.
         */
        void loadMap(std::string p_mapName, Graphics &p_graphics);

};

struct Tileset{
    SDL_Texture* Texture;
    int FirstGid;

    Tileset(){
        this->FirstGid = -1;
    }

    Tileset(SDL_Texture* p_texture, int p_firstGid):
        Texture(p_texture),
        FirstGid(p_firstGid)
    {}
};

#endif /* LEVEL */