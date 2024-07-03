#ifndef LEVEL
#define LEVEL

#include "globals.h"
class Graphics;
struct SDL_Texture;

#include <string>

class Level{
    public:
        Level();
        Level(std::string p_mapName, Vector2f p_spawnPoint, Graphics &p_graphics);
        ~Level();

        void update(int p_elapsedTime);
        void draw(Graphics &p_graphics);

    private:
        std::string _mapName;
        Vector2f _spawnPoint;
        Vector2f _size;
        SDL_Texture* _backgroundTexture;

        void loadMap(std::string p_mapName, Graphics &p_graphics);
};

#endif /* LEVEL */
