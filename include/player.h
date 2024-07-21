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
#include "slope.h"
#include "level.h"
#include "enemy.h"
#include "object.h"

#include <string>

class Graphics;
class Door;

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
    Player(Graphics &p_graphics, Vector2f p_spawnPoint);

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
     * @brief Makes the player look up.
     */
    void lookUp();

    /**
     * @brief Stops the player from looking up.
     */
    void stopLookingUp();

    /**
     * @brief Makes the player look down.
     */
    void lookDown();

    /**
     * @brief Stops the player from looking down.
     */
    void stopLookingDown();

    /**
     * @brief Makes the player jump.
     */
    void jump();

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

    /**
     * @brief Handles collisions with tiles.
     * 
     * @param p_others A vector of rectangles representing the tiles.
     */
    void handleTileCollisions(std::vector<Rectangle> &p_others);

    /**
     * @brief Handles collisions with object.
     * 
     * @param p_others A vector of rectangles representing the objects.
     */
    void handleObjectCollisions(std::vector<Object> &p_others);

    /**
     * @brief Handles collisions with slopes.
     * 
     * @param p_others A vector of slopes.
     */
    void handleSlopeCollisions(std::vector<Slope> &p_others);

    /**
     * @brief Handles collisions with doors.
     * 
     * @param p_others A vector of doors.
     * @param p_level The current level.
     * @param p_graphics The graphics context.
     */
    void handleDoorCollision(std::vector<Door> &p_others, Level &p_level, Graphics &p_graphics);

    /**
     * @brief Handles collisions with enemies.
     * 
     * @param p_others A vector of pointers to enemies.
     */
    void handleEnemyCollision(std::vector<Enemy*> &p_others);

    /**
     * @brief Gets the x-coordinate of the player.
     * 
     * @return float: The x-coordinate.
     */
    inline float getX() const { return this->_x; }

    /**
     * @brief Gets the y-coordinate of the player.
     * 
     * @return float: The y-coordinate.
     */
    inline float getY() const { return this->_y; }

    /**
     * @brief Gets the maximum health of the player.
     * 
     * @return int: The maximum health.
     */
    inline int getMaxHealth() const { return this->_maxHealth; }

    /**
     * @brief Gets the current health of the player.
     * 
     * @return int: The current health.
     */
    inline int getCurrentHealth() const { return this->_currentHealth; }

    /**
     * @brief Increases the player's health by a specified amount.
     * 
     * @param p_amount The amount of health to gain.
     */
    void gainHealth(int p_amount);

    /**
     * @brief Resets the level when the player dies.
     * 
     * @param p_level The current level.
     * @param p_graphics The graphics context.
     */
    void resetLevelOnDeath(Level &p_level, Graphics &p_graphics);

private:
    float _dx, _dy; ///< Delta x and y for player's movement.
    Direction _facing; ///< Current direction the player is facing.
    bool _grounded; ///< True/False depending on if the player is on the ground or not.

    bool _lookingUp; ///< True/False depending on if the player is looking up.
    bool _lookingDown; ///< True/False depending on if the player is looking down.
    
    int _maxHealth; ///< The maximum health of the player.
    int _currentHealth; ///< The current health of the player.
};

#endif /* PLAYER */