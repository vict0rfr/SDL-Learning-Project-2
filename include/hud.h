/**
 * @file hud.h
 * @brief Defines the Hud class and its associated methods.
 */

#ifndef HUD
#define HUD

#include "sprite.h"
#include "player.h"

class Graphics;

/**
 * @class Hud
 * @brief Represents the Heads-Up Display (HUD) in the game.
 * 
 * The Hud class handles the display of various game information such as the player's health,
 * experience points, and weapon information.
 */
class Hud {
public:
    /**
     * @brief Default constructor for Hud.
     */
    Hud();

    /**
     * @brief Constructs a Hud object with specified graphics context and player reference.
     * 
     * @param p_graphics The graphics context.
     * @param p_player Reference to the player object.
     */
    Hud(Graphics &p_graphics, Player &p_player);

    /**
     * @brief Updates the HUD with the latest game information.
     * 
     * @param p_elapsedTime Time elapsed since the last update.
     * @param p_player Reference to the player object.
     */
    void update(int p_elapsedTime, Player &p_player);

    /**
     * @brief Draws the HUD on the screen.
     * 
     * @param p_graphics Graphics context to draw the HUD.
     */
    void draw(Graphics &p_graphics);

private:
    Player _player; ///< Reference to the player object.

    // Health sprites
    Sprite _healthBarSprite; ///< Sprite for the health bar.
    Sprite _healthNumber1; ///< Sprite for the health number.
    Sprite _currentHealthBar; ///< Sprite for the current health bar.

    // Experience sprites
    Sprite _lvWord; ///< Sprite for the level word.
    Sprite _lvNumber; ///< Sprite for the level number.
    Sprite _expBar; ///< Sprite for the experience bar.

    // Weapon info sprites
    Sprite _slash; ///< Sprite for the slash weapon.
    Sprite _dashes; ///< Sprite for the dashes weapon.
};

#endif /* HUD */