#include <SDL2/SDL.h>
#include <iostream>

#include "game.h"
#include "graphics.h"
#include "input.h"

/*
Main game loop
*/

namespace{
    const int FPS = 50;
    const int MAX_FRAME_TIME = 5 * 1000 / FPS;
}

/*
Initializes SDL components and calls the gameLoop()
*/
Game::Game(){
    SDL_Init(SDL_INIT_EVERYTHING);
    this->gameLoop();
}

/*
Will destroy everything
*/
Game::~Game(){

}

/*
The gameLoop() will take in all inputs made by the player
and will draw textures to the screen
*/
void Game::gameLoop(){
    Graphics graphics;
    Input input;
    SDL_Event e;

    this->_player = Sprite(graphics, "../res/gfx/MyChar.png", 0, 0, 16, 16, 100, 100);


    int LAST_UPDATE_TIME = SDL_GetTicks64();

    while(true){
        input.beginNewFrame();

        if(SDL_PollEvent(&e)){
            if(e.type == SDL_KEYDOWN){
                if(e.key.repeat == 0){
                    input.keyDownEvent(e);
                }
            } else if(e.type == SDL_KEYUP){
                input.keyUpEvent(e);
            } else if(e.type == SDL_QUIT){
                return;
            }
        }
        if(input.wasKeyPressed(SDL_SCANCODE_ESCAPE)){
            return;
        }

        const int CURRENT_TIME_MS = SDL_GetTicks64();
        int ELAPSED_TIME_MS = CURRENT_TIME_MS - LAST_UPDATE_TIME;
        this->update(std::min(ELAPSED_TIME_MS, MAX_FRAME_TIME));
        LAST_UPDATE_TIME = CURRENT_TIME_MS;

        this->draw(graphics);
    }
}


void Game::draw(Graphics &p_graphics){
    p_graphics.clear();

    this->_player.draw(p_graphics, 100, 100);

    p_graphics.flip();

}

void Game::update(float p_elapsedTime){

}