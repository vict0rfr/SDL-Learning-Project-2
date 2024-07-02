#ifndef GAME_H
#define GAME_H

#include "sprite.h"

class Graphics;

class Game{
    public:
        Game();
        ~Game();
    private:
        void gameLoop();
        void draw(Graphics &p_graphics);
        void update(float p_elapsedTime);

        Sprite _player;
};

#endif