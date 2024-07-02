#ifndef SPRITE
#define SPRITE

#include <SDL2/SDL.h>
#include <string>

class Graphics;

/**
 * @class Sprite
 * @brief Holds all information for individual sprites.
 * 
 * This class is responsible for managing the properties of a sprite,
 * including its texture, position, and rendering.
 */
class Sprite{
public:
    /**
     * @brief Default constructor.
     * 
     * Initializes a new instance of the Sprite class with default parameters.
     */
    Sprite();
    
    /**
     * @brief Overloaded constructor.
     * 
     * Initializes a new instance of the Sprite class with specific attributes.
     * 
     * @param p_graphics Reference to the Graphics object for rendering.
     * @param p_filePath Path to the sprite sheet file.
     * @param p_sourceX X position in the sprite sheet.
     * @param p_sourceY Y position in the sprite sheet.
     * @param p_width Width of the sprite.
     * @param p_height Height of the sprite.
     * @param p_posX Initial X position of the sprite.
     * @param p_posY Initial Y position of the sprite.
     */
    Sprite(Graphics &p_graphics, const std::string &p_filePath, int p_sourceX, 
           int p_sourceY, int p_width, int p_height, float p_posX, float p_posY);
    
    /**
     * @brief Virtual destructor.
     */
    virtual ~Sprite();
    
    /**
     * @brief Updates the sprite's state.
     * 
     * This method should be overridden by derived classes to update the sprite's state
     * for each frame.
     */
    virtual void update();
    
    /**
     * @brief Draws the sprite.
     * 
     * Renders the sprite at the specified position.
     * 
     * @param p_graphics Reference to the Graphics object for rendering.
     * @param p_x X position where the sprite should be drawn.
     * @param p_y Y position where the sprite should be drawn.
     */
    void draw(Graphics &p_graphics, int p_x, int p_y);
protected:
    SDL_Rect _src; ///< Source rectangle in the sprite sheet.
    SDL_Texture* _spriteSheet; ///< Texture of the sprite sheet.
    float _x, _y; ///< Current position of the sprite.
private:
};

#endif /* SPRITE */