#ifndef HUD
#define HUD

#include "sprite.h"
#include "player.h"

class Graphics;

class Hud {
    public:
        Hud();
        Hud(Graphics &p_graphics, Player &p_player);
        void update(int p_elapsedTime, Player &p_player);
        void draw (Graphics &p_graphics);
    private:
        Player _player;

        // health sprites
        Sprite _healthBarSprite;
        Sprite _healthNumber1;
        Sprite _currentHealthBar;

        //exp sprites
        Sprite _lvWord;
        Sprite _lvNumber;
        Sprite _expBar;

        //weapon info
        Sprite _slash;
        Sprite _dashes;
};
#endif