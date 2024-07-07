#ifndef HUD
#define HUD

#include "sprite.h"
#include "player.h"

class Graphics;

class Hud {
    public:
        Hud();
        Hud(Graphics &p_graphics, Player &p_player);
        void update(int p_elapsedTime);
        void draw (Graphics &p_graphics);
    private:
        Player _player;

        Sprite _healthBarSprite;
        Sprite _healthNumber1;
};
#endif