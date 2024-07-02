#ifndef GRAPHICS_H
#define GRAPHICS_H

/*
Holds all info for graphics of the game
*/

#include <map>
#include <string>

struct SDL_Window;
struct SDL_Renderer;

class Graphics {
    public:
        /*
        Constructer that will initiliaze the window and the renderer.
        Also sets the window title to Cavestory
        */
        Graphics();

        /*
        Will destroy everything and free memory
        */
        ~Graphics();

        /* SDL_Surface* loadImage
        Loads an image onto _spriteSheets map if it doesn't already exist.
        Each image will be only loaded once. Returns the image from the map
        regardless of whether it was just loaded or not.
        */
        SDL_Surface* loadImage(const std::string &p_filePath);

        /* void blitSurface
        Draws a given texture (p_texture) onto a part of the screen 
        determined by p_dst. p_src will determine what part of p_texture
        to be drawn/rendered.
        */
        void blitSurface(SDL_Texture* p_texture, SDL_Rect* p_src, SDL_Rect* p_dst);

        /* void flip
        Renders everything on the screen
        */
        void flip();

        /* void clear
        Clears the screen
        */
        void clear();

        /*SDL_Renderer* getRenderer
        Returns the instance's renderer
        */
        SDL_Renderer* getRenderer() const;
    private:
        SDL_Window* _window;
        SDL_Renderer* _renderer;

        std::map<std::string, SDL_Surface*> _spriteSheets;
};


#endif // GRAPHICS_H