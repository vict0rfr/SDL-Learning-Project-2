/**
 * @file tile.h
 * @brief Tile class definition for representing a single tile in the game.
 * 
 * This file defines the Tile class, which is used to represent individual tiles within the game's levels.
 * Tiles are the basic building blocks of the game's maps, and this class handles their rendering and basic properties.
 */

#ifndef TILE
#define TILE

#include "globals.h"

struct SDL_Texture;
class Graphics;

/**
 * @class Tile
 * @brief Represents a single tile in the game.
 * 
 * The Tile class encapsulates the properties and behavior of a single tile in the game's world.
 * It includes information about the tile's texture, size, position in the tileset, and position in the world.
 */
class Tile{
     public:
        /**
         * @brief Default constructor. Initializes an empty tile.
         */
        Tile();

        /**
         * @brief Constructs a Tile with specified properties.
         * 
         * @param p_tileset Pointer to the SDL_Texture object representing the tileset image.
         * @param p_size Size of the tile in pixels.
         * @param p_tilesetPosition Position of the tile within the tileset.
         * @param p_position Position of the tile in the game world.
         */
        Tile(SDL_Texture* p_tileset, Vector2f p_size, Vector2f p_tilesetPosition, Vector2f p_position);

        /**
         * @brief Updates the tile's state.
         * 
         * This function currently does not perform any operations but can be used for animated tiles or tiles with dynamic behavior.
         * 
         * @param p_elapsedTime Time elapsed since the last update.
         */
        void update(int p_elapsedTime);

        /**
         * @brief Draws the tile to the screen.
         * 
         * @param p_graphics Graphics context used for drawing.
         */
        void draw(Graphics &p_graphics);

     protected:
        SDL_Texture* _tileset; ///< Pointer to the SDL_Texture object for the tileset.
        Vector2f _size; ///< Size of the tile.
        Vector2f _tilesetPosition; ///< Position of the tile within the tileset.
        Vector2f _position; ///< Position of the tile in the game world.
};

#endif /* TILE */
