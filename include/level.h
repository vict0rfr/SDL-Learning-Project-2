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
#include "door.h"

class Graphics;
class Enemy;
class Player;
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
     * @param p_graphics Graphics context for rendering the level.
     */
    Level(std::string p_mapName, Graphics &p_graphics);

    /**
     * @brief Destructor. Cleans up resources used by the level.
     */
    ~Level();

    /**
     * @brief Updates the level state.
     * 
     * @param p_elapsedTime Time elapsed since the last update call.
     */
    void update(int p_elapsedTime, Player &p_player, Graphics &p_graphics);

    /**
     * @brief Draws the level to the screen.
     * 
     * @param p_graphics Graphics context used for rendering.
     */
    void draw(Graphics &p_graphics);

    /**
     * @brief Checks for collisions with tiles.
     * 
     * @param p_other The rectangle to check for collisions.
     * @return std::vector<Rectangle> A vector of rectangles representing the colliding tiles.
     */
    std::vector<Rectangle> checkTileCollisions(const Rectangle &p_other);

    /**
     * @brief Checks for collisions with slopes.
     * 
     * @param p_other The rectangle to check for collisions.
     * @return std::vector<Slope> A vector of slopes representing the colliding slopes.
     */
    std::vector<Slope> checkSlopeCollisions(const Rectangle &p_other);

    /**
     * @brief Checks for collisions with doors.
     * 
     * @param p_other The rectangle to check for collisions.
     * @return std::vector<Door> A vector of doors representing the colliding doors.
     */
    std::vector<Door> checkDoorCollisions(const Rectangle &p_other);

    /**
     * @brief Checks for collisions with enemies.
     * 
     * @param p_other The rectangle to check for collisions.
     * @return std::vector<Enemy*> A vector of pointers to enemies representing the colliding enemies.
     */
    std::vector<Enemy*> checkEnemyCollisions(const Rectangle &p_other);

    /**
     * @brief Gets the player's spawn point in the level.
     * 
     * @return Vector2f The player's spawn point.
     */
    const Vector2f getPlayerSpawnPoint() const;
    
private:
    std::string _mapName; ///< Name of the map file for the level.

    Vector2f _spawnPoint; ///< Initial spawn point within the level.
    Vector2f _size; ///< Size of the level.
    Vector2f _tileSize; ///< Size of the tile.

    SDL_Texture* _backgroundTexture; ///< Texture for the level's background.

    std::vector<Tile> _tileList; ///< List of tiles in the level.
    std::vector<Tileset> _tilesets; ///< List of tilesets used in the level.
    std::vector<Rectangle> _collisionRects; ///< List of rectangles for collision detection.
    std::vector<Slope> _slopes; ///< List of slopes in the level.

    std::vector<AnimatedTile> _animatedTileList; ///< List of animated tiles in the level.
    std::vector<AnimatedTileInfo> _animatedTileInfo; ///< Information about animated tiles.
    std::vector<Door> _doorList; ///< List of doors in the level.
    std::vector<Enemy*> _enemies; ///< List of enemies in the level.

    /**
     * @brief Gets the position of a tile in the tileset.
     * 
     * @param p_tls The tileset.
     * @param p_gid The global tile ID.
     * @param p_tileWidth The width of the tile.
     * @param p_tileHeight The height of the tile.
     * @return Vector2f The position of the tile in the tileset.
     */
    Vector2f getTilesetPosition(Tileset p_tls, int p_gid, int p_tileWidth, int p_tileHeight);

    /**
     * @brief Loads the map and resources for the level.
     * 
     * @param p_mapName Name of the map file to load.
     * @param p_graphics Graphics context used for loading textures.
     */
    void loadMap(std::string p_mapName, Graphics &p_graphics);
};

/**
 * @struct Tileset
 * @brief Represents a tileset used in the level.
 * 
 * The Tileset struct holds a texture and the first global tile ID for the tileset.
 */
struct Tileset {
    SDL_Texture* Texture; ///< Texture for the tileset.
    int FirstGid; ///< First global tile ID in the tileset.

    /**
     * @brief Default constructor for Tileset.
     */
    Tileset() {
        this->FirstGid = -1;
    }

    /**
     * @brief Constructs a Tileset with specified texture and first global tile ID.
     * 
     * @param p_texture The texture for the tileset.
     * @param p_firstGid The first global tile ID in the tileset.
     */
    Tileset(SDL_Texture* p_texture, int p_firstGid) :
        Texture(p_texture),
        FirstGid(p_firstGid)
    {}
};

#endif /* LEVEL */