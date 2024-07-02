#include "input.h"

void Input::beginNewFrame(){
    this->_pressedKeys.clear();
    this->_releasedKeys.clear();
}

/*
Method is called when a key is pressed, 
if a key is pressed, it is also held, hence why both
members are set to true.
*/
void Input::keyDownEvent(const SDL_Event& e){
    this->_pressedKeys[e.key.keysym.scancode] = true;
    this->_heldKeys[e.key.keysym.scancode] = true;
}

/*
Method is called when a key is released,
previously being held/pressed. keyUpEvent() will set _heldKeys
to false, as the key is not held anymore and will also 
set _releasedKeys to true as the key was just released.
*/
void Input::keyUpEvent(const SDL_Event& e){
    this->_releasedKeys[e.key.keysym.scancode] = true;
    this->_heldKeys[e.key.keysym.scancode] = false;
}

/*
Returns true/false if p_key was pressed
*/
bool Input::wasKeyPressed(SDL_Scancode p_key){
    return this->_pressedKeys[p_key];
}

/*
Returns true/false if p_key was released
*/
bool Input::wasKeyReleased(SDL_Scancode p_key){
    return this->_releasedKeys[p_key];
}

/*
Returns true/false if p_key is being held */
bool Input::isKeyHeld(SDL_Scancode p_key){
    return this->_heldKeys[p_key];
}