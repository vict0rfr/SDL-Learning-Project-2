#ifndef DOOR
#define DOOR

#include "rectangle.h"
#include "globals.h"

#include <string>

class Door : public Rectangle{
    public:
        Door(){}
        Door(Rectangle p_r, std::string p_destination):
            Rectangle(p_r.getLeft() * globals::SPRITE_SCALE,
                p_r.getTop() * globals::SPRITE_SCALE,
                p_r.getWidth() * globals::SPRITE_SCALE,
                p_r.getHeight() * globals::SPRITE_SCALE),
            _destination(p_destination)
        {}

        const inline Rectangle getRectangle() const { return this->getRect(); }
        const inline std::string getDestination() const { return this->_destination; }
    private:
        std::string _destination;
};

#endif /* DOOR */
