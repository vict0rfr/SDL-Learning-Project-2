/**
 * @file enemy.h
 * @brief Defines the Enemy class and its derived classes.
 */

#ifndef ENEMY
#define ENEMY

#include "animatedSprite.h"
#include "globals.h"
#include "player.h"

#include <string>

class Graphics;

/**
 * @class Enemy
 * @brief Represents a generic enemy in the game.
 * 
 * The Enemy class is an abstract base class for all enemies in the game. It handles
 * common functionality such as health, direction, and invincibility.
 */
class Enemy : public AnimatedSprite {
public:
    /**
     * @brief Default constructor for Enemy.
     */
    Enemy();

    /**
     * @brief Constructs an Enemy object with specified parameters.
     * 
     * @param p_graphics The graphics context.
     * @param p_filePath The file path to the sprite sheet.
     * @param p_sourceX The x-coordinate of the sprite in the sprite sheet.
     * @param p_sourceY The y-coordinate of the sprite in the sprite sheet.
     * @param p_width The width of the sprite.
     * @param p_height The height of the sprite.
     * @param p_spawnPoint The initial spawn point of the enemy.
     * @param p_timeToUpdate The time to update the animation.
     */
    Enemy(Graphics &p_graphics, std::string p_filePath, int p_sourceX, int p_sourceY,
          int p_width, int p_height, Vector2f p_spawnPoint, int p_timeToUpdate);

    /**
     * @brief Updates the enemy's state.
     * 
     * @param p_elapsedTime Time elapsed since the last update.
     * @param p_player Reference to the player object.
     */
    virtual void update(int p_elapsedTime, Player &p_player);

    /**
     * @brief Draws the enemy on the screen.
     * 
     * @param p_graphics Graphics context to draw the enemy.
     */
    virtual void draw(Graphics &p_graphics);

    /**
     * @brief Handles the interaction when the enemy touches the player.
     * 
     * @param p_player Pointer to the player object.
     */
    virtual void touchPlayer(Player* p_player) = 0;

    /**
     * @brief Gets the maximum health of the enemy.
     * 
     * @return int: The maximum health.
     */
    inline int getMaxHealth() const { return this->_maxHealth; }

    /**
     * @brief Gets the current health of the enemy.
     * 
     * @return int: The current health.
     */
    inline int getCurrentHealth() const { return this->_currentHealth; }

protected:
    Direction _direction; ///< The current direction the enemy is facing.

    int _maxHealth; ///< The maximum health of the enemy.
    int _currentHealth; ///< The current health of the enemy.

    bool _isInvicible; ///< True if the enemy is invincible.
    float _invincibilityDuration; ///< Duration of the invincibility.
    float _invincibilityTimer; ///< Timer for the invincibility.
};

/**
 * @class Bat
 * @brief Represents a bat enemy in the game.
 * 
 * The Bat class is a specific type of enemy that has its own unique behavior and animations.
 * Create new child classes to add new enemies in the future
 */
class Bat : public Enemy {
public:
    /**
     * @brief Default constructor for Bat.
     */
    Bat();

    /**
     * @brief Constructs a Bat object with specified parameters.
     * 
     * @param p_graphics The graphics context.
     * @param p_spawnPoint The initial spawn point of the bat.
     */
    Bat(Graphics &p_graphics, Vector2f p_spawnPoint);

    /**
     * @brief Updates the bat's state.
     * 
     * @param p_elapsedTime Time elapsed since the last update.
     * @param p_player Reference to the player object.
     */
    void update(int p_elapsedTime, Player &p_player);

    /**
     * @brief Draws the bat on the screen.
     * 
     * @param p_graphics Graphics context to draw the bat.
     */
    void draw(Graphics &p_graphics);

    /**
     * @brief Handles the interaction when the bat touches the player.
     * 
     * @param p_player Pointer to the player object.
     */
    void touchPlayer(Player* p_player);

private:
    /**
     * @brief Callback for when an animation is completed.
     * 
     * @param p_currentAnimation The current animation that just finished.
     */
    void animationDone(std::string p_currentAnimation);

    /**
     * @brief Sets up the animations for the bat.
     */
    void setupAnimations();

    float _startingX; ///< The starting x-coordinate of the bat.
    float _startingY; ///< The starting y-coordinate of the bat.
    bool _shouldMoveUp; ///< True if the bat should move up.
};

#endif /* ENEMY */