#ifndef ENEMY
#define ENEMY

#include "animatedSprite.h"
#include "globals.h"
#include "player.h"

#include <string>

class Graphics;

class Enemy : public AnimatedSprite {
    public:
        Enemy();
        Enemy(Graphics &p_graphics, std::string p_filePath, int p_sourceX, int p_sourceY,
            int p_width, int p_height, Vector2f p_spawnPoint, int p_timeToUpdate);

        virtual void update(int p_elapsedTime, Player &p_player);
        virtual void draw(Graphics &p_graphics);
        virtual void touchPlayer(Player* p_player) = 0;

        inline int getMaxHealth() const { return this->_maxHealth; }
        inline int getCurrentHealth() const { return this->_currentHealth; }
    protected:
        Direction _direction;

        int _maxHealth;
        int _currentHealth;
};

class Bat : public Enemy{
    public:
        Bat();
        Bat(Graphics &p_graphics, Vector2f p_spawnPoint);
        void update(int p_elapsedTime, Player &p_player);
        void draw(Graphics &p_graphics);
        void touchPlayer(Player* p_player);

        void animationDone(std::string p_currentAnimation);
        void setupAnimations();

        float _startingX, _startingY;
        bool _shouldMoveUp;
};

#endif /* ENEMY */
