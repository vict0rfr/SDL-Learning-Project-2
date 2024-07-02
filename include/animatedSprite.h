/**
 * @file animatedSprite.h
 * @brief Defines the AnimatedSprite class, which is used to handle animated sprites.
 */

#ifndef ANIMATEDSPRITE_H
#define ANIMATEDSPRITE_H

#include "sprite.h"
#include "globals.h"
#include <string>
#include <map>
#include <vector>

class Graphics;

/**
 * @class AnimatedSprite
 * @brief A class for handling animated sprites.
 * 
 * Inherits from the Sprite class and adds functionality for animating sprites by cycling through frames.
 */
class AnimatedSprite : public Sprite {
public:
    /**
     * @brief Default constructor.
     */
    AnimatedSprite();

    /**
     * @brief Constructs an AnimatedSprite with animation properties.
     * @param p_graphics Reference to the Graphics object for rendering.
     * @param p_filePath Path to the sprite sheet.
     * @param p_sourceX X position in the sprite sheet.
     * @param p_sourceY Y position in the sprite sheet.
     * @param p_width Width of a single frame.
     * @param p_height Height of a single frame.
     * @param p_posX X position on the screen.
     * @param p_posY Y position on the screen.
     * @param p_timeToUpdate Time between animation frames.
     */
    AnimatedSprite(Graphics &p_graphics, const std::string &p_filePath, int p_sourceX, 
                   int p_sourceY, int p_width, int p_height, float p_posX,
                   float p_posY, float p_timeToUpdate);

    /**
     * @brief Plays the specified animation.
     * @param p_animation Name of the animation to play.
     * @param p_once Whether the animation should only play once.
     */
    void playAnimation(std::string p_animation, bool p_once = false);

    /**
     * @brief Updates the sprite animation based on elapsed time.
     * @param p_elapsedTime Time elapsed since the last update.
     */
    void update(int p_elapsedTime);

    /**
     * @brief Draws the sprite at the given position.
     * @param p_graphics Reference to the Graphics object for rendering.
     * @param p_x X position on the screen.
     * @param p_y Y position on the screen.
     */
    void draw(Graphics &p_graphics, int p_x, int p_y);

    /**
     * @brief Sets up the animations for the sprite. Should be overridden by derived classes.
     */
    virtual void setupAnimations();

protected:
    double _timeToUpdate; ///< Time between animation frames.
    bool _currentAnimationOnce; ///< Whether the current animation should only play once.
    std::string _currentAnimation; ///< Name of the current animation.

    /**
     * @brief Adds an animation to the sprite.
     * @param p_frames Number of frames in the animation.
     * @param p_x X position in the sprite sheet.
     * @param p_y Y position in the sprite sheet.
     * @param p_name Name of the animation.
     * @param p_width Width of a single frame.
     * @param p_height Height of a single frame.
     * @param p_offset Offset to apply to each frame.
     */
    void addAnimation(int p_frames, int p_x, int p_y, std::string p_name, int p_width, int p_height, Vector2f p_offset);

    /**
     * @brief Resets all animations for the sprite.
     */
    void resetAnimations();

    /**
     * @brief Stops the current animation.
     */
    void stopAnimation();

    /**
     * @brief Sets the visibility of the sprite.
     * @param p_visible Whether the sprite should be visible.
     */
    void setVisible(bool p_visible);

    /**
     * @brief Called when an animation is completed.
     * @param p_currentAnimation The animation that just finished.
     */
    virtual void animationDone(std::string p_currentAnimation);

private:
    std::map<std::string, std::vector<SDL_Rect>> _animations; ///< Map of animation names to frame rectangles.
    std::map<std::string, Vector2f> _offests; ///< Map of animation names to offsets.

    int _frameIndex; ///< Index of the current frame in the animation.
    double _timeElapsed; ///< Time elapsed since the last frame change.
    bool _visible; ///< Whether the sprite is currently visible.
};

#endif /* ANIMATEDSPRITE_H */