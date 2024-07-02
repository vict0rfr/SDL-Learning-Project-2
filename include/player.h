/**
 * @file player.h
 * @brief Player class definition, inheriting from AnimatedSprite.
 * 
 * The Player class represents a player character in the game. It inherits from the AnimatedSprite class,
 * allowing it to have animated movements. The class provides functionality for player movement, including
 * moving left, right, and stopping. It also handles player animations.
 */

#ifndef PLAYER
#define PLAYER

#include "animatedSprite.h"
#include "globals.h"

#include <string>

class Graphics;

/**
 * @class Player
 * @brief Represents a player character with animated movements.
 * 
 * This class is responsible for handling the player character's animations and movements within the game.
 * It inherits from the AnimatedSprite class to utilize animated sprites for the player character.
 */
class Player : public AnimatedSprite {
    public:
        /**
         * @brief Default constructor for Player.
         */
        Player();

        /**
         * @brief Constructs a Player with graphics context, and initial position.
         * 
         * @param p_graphics Graphics context to draw the player.
         * @param p_x Initial x-coordinate of the player.
         * @param p_y Initial y-coordinate of the player.
         */
        Player(Graphics &p_graphics, float p_x, float p_y);

        /**
         * @brief Draws the player on the screen.
         * 
         * @param p_graphics Graphics context to draw the player.
         */
        void draw(Graphics &p_graphics);

        /**
         * @brief Updates the player's position and animations.
         * 
         * @param p_elapsedTime Time elapsed since the last update.
         */
        void update(float p_elapsedTime);

        /**
         * @brief Moves the player left by -dx.
         */
        void moveLeft();

        /**
         * @brief Moves the player right by +dx.
         */
        void moveRight();

        /**
         * @brief Stops the player's movement (dx = 0).
         */
        void stopMoving();

        /**
         * @brief Callback for when an animation is completed.
         * 
         * @param p_currentAnimation The current animation that just finished.
         */
        virtual void animationDone(std::string p_currentAnimation);

        /**
         * @brief Sets up the animations for the player.
         */
        virtual void setupAnimations();

    private:
        float _dx, _dy; ///< Delta x and y for player's movement.

        Direction _facing; ///< Current direction the player is facing.
};

#endif /* PLAYER */