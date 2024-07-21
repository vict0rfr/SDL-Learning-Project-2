#include <SDL2/SDL.h>
#include <iostream>

#include "game.h"
#include "graphics.h"
#include "input.h"
#include "hud.h"

namespace{
    const int FPS = 50;
    const int MAX_FRAME_TIME = 1000 / FPS;
}

Game::Game(){
    SDL_Init(SDL_INIT_EVERYTHING);
    this->gameLoop();
}

Game::~Game(){

}

void Game::gameLoop(){
    Graphics graphics;
    Input input;
    SDL_Event e;

    this->_level = Level("Map 1", graphics);
    this->_player = Player(graphics, this->_level.getPlayerSpawnPoint());
    this->_hud = Hud(graphics, this->_player);

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
        else if(input.isKeyHeld(SDL_SCANCODE_LEFT) == true){
            this->_player.moveLeft();
        }
        else if(input.isKeyHeld(SDL_SCANCODE_RIGHT) == true){
            this->_player.moveRight();
        }

        if(input.isKeyHeld(SDL_SCANCODE_UP) == true){
            this->_player.lookUp();
        }
        else if(input.isKeyHeld(SDL_SCANCODE_DOWN) == true){
            this->_player.lookDown();
        }

        if(input.wasKeyReleased(SDL_SCANCODE_UP) == true){
            this->_player.stopLookingUp();
        }
        if(input.wasKeyReleased(SDL_SCANCODE_DOWN) == true){
            this->_player.stopLookingDown();
        }
        if(input.wasKeyPressed(SDL_SCANCODE_SPACE) || input.isKeyHeld(SDL_SCANCODE_SPACE)){
            this->_player.jump();
        }

        if(!input.isKeyHeld(SDL_SCANCODE_LEFT) && !input.isKeyHeld(SDL_SCANCODE_RIGHT)){
            this->_player.stopMoving();
        }

        const int CURRENT_TIME_MS = SDL_GetTicks64();
        int ELAPSED_TIME_MS = CURRENT_TIME_MS - LAST_UPDATE_TIME;

        this->_graphics = graphics;
        this->update(std::min(ELAPSED_TIME_MS, MAX_FRAME_TIME), graphics);
        LAST_UPDATE_TIME = CURRENT_TIME_MS;

        this->draw(graphics);
    }
}

void Game::draw(Graphics &p_graphics){
    p_graphics.clear();

    this->_level.draw(p_graphics);
    this->_player.draw(p_graphics);
    this->_hud.draw(p_graphics);

    p_graphics.flip();
}

void Game::update(float p_elapsedTime, Graphics &p_graphics){
    this->_player.update(p_elapsedTime);
    this->_level.update(p_elapsedTime, this->_player, p_graphics);
    this->_hud.update(p_elapsedTime, this->_player);

    std::vector<Rectangle> others;
    if((others = this->_level.checkTileCollisions(this->_player.getBoundingBox())).size() > 0){
        //player collided with at least one tile
        this->_player.handleTileCollisions(others);
    }

    std::vector<Object> o_others;
    if((o_others = this->_level.checkObjectCollisions(this->_player.getBoundingBox())).size() > 0){
        //player collided with at least one tile
        this->_player.handleObjectCollisions(o_others);
    }

    std::vector<Slope> s_others;
    if((s_others = this->_level.checkSlopeCollisions(this->_player.getBoundingBox())).size() > 0){
        this->_player.handleSlopeCollisions(s_others);
    }

    std::vector<Door> d_others;
    if((d_others = this->_level.checkDoorCollisions(this->_player.getBoundingBox())).size() > 0){
        this->_player.handleDoorCollision(d_others, this->_level, this->_graphics);
    }

    std::vector<Enemy*> e_others;
    if((e_others = this->_level.checkEnemyCollisions(this->_player.getBoundingBox())).size() > 0){
        this->_player.handleEnemyCollision(e_others);
    }
}