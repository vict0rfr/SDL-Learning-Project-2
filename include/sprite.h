#ifndef SPRITE
#define SPRITE

#include <SDL2/SDL.h>
#include <string>

class Graphics;

/* Sprite class
Holds all information for an individual sprites
*/
class Sprite{
    public:
        Sprite();
        Sprite(Graphics &p_graphics, const std::string &p_filePath, int p_sourceX, 
        int p_sourceY, int p_width, int p_height, float p_posX, float p_posY);
        virtual ~Sprite();
        virtual void update();
        void draw(Graphics &p_graphics, int p_x, int p_y);
    private:
        SDL_Rect _src;
        SDL_Texture* _spriteSheet;

        float _x, _y;
};

#endif /* SPRITE */
