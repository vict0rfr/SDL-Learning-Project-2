/**
 * @file animatedTile.h
 * @brief Defines the AnimatedTile class and its associated methods and structures.
 */

#ifndef ANIMATEDTILE
#define ANIMATEDTILE

#include "tile.h"
#include "globals.h"

#include <vector>

/**
 * @class AnimatedTile
 * @brief Represents a tile that can animate by cycling through different tile positions.
 * 
 * The AnimatedTile class inherits from the Tile class and adds functionality for animating
 * the tile by cycling through a series of tileset positions over a specified duration.
 */
class AnimatedTile : public Tile {
public:
    /**
     * @brief Constructs an AnimatedTile with specified tileset positions, duration, texture, size, and position.
     * 
     * @param p_tilesetPositions A vector of positions in the tileset for the animation frames.
     * @param p_duration Duration of the animation cycle in milliseconds.
     * @param p_tileset Pointer to the SDL_Texture containing the tileset.
     * @param p_size Size of the tile.
     * @param p_position Position of the tile in the level.
     */
    AnimatedTile(std::vector<Vector2f> p_tilesetPositions, int p_duration, 
                 SDL_Texture* p_tileset, Vector2f p_size, Vector2f p_position);

    /**
     * @brief Updates the animation state based on the elapsed time.
     * 
     * @param p_elapsedTime Time elapsed since the last update call in milliseconds.
     */
    void update(int p_elapsedTime);

    /**
     * @brief Draws the animated tile to the screen.
     * 
     * @param p_graphics Reference to the Graphics object used for rendering.
     */
    void draw(Graphics &p_graphics);

protected:
    int _amountOfTime = 0; ///< Accumulated time since the last frame change.
    bool _notDone = false; ///< Flag indicating whether the animation is still running.

private:
    std::vector<Vector2f> _tilesetPositions; ///< Positions in the tileset for the animation frames.
    int _tileToDraw; ///< Index of the current tile to draw.
    int _duration; ///< Duration of the animation cycle in milliseconds.
};

/**
 * @struct AnimatedTileInfo
 * @brief Holds information about an animated tile, including its tileset and animation frames.
 * 
 * The AnimatedTileInfo struct contains metadata about an animated tile, such as the first GID
 * of the tileset, the starting tile ID, the IDs of the animation frames, and the duration of the animation.
 */
struct AnimatedTileInfo {
public:
    int TilesetsFirstGid; ///< First global tile ID in the tileset.
    int StartTileId; ///< Starting tile ID for the animation.
    std::vector<int> TileIds; ///< IDs of the tiles used in the animation.
    int Duration; ///< Duration of the animation cycle in milliseconds.
};

#endif /* ANIMATEDTILE */