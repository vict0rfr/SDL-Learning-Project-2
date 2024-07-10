/**
 * @file door.h
 * @brief Defines the Door class and its associated methods.
 */

#ifndef DOOR
#define DOOR

#include "rectangle.h"
#include "globals.h"

#include <string>

/**
 * @class Door
 * @brief Represents a door in the game that can lead to different destinations.
 * 
 * The Door class inherits from the Rectangle class and adds functionality to specify
 * a destination that the door leads to.
 */
class Door : public Rectangle {
public:
    /**
     * @brief Default constructor for Door.
     */
    Door() {}

    /**
     * @brief Constructs a Door object with specified rectangle and destination.
     * 
     * @param p_r The rectangle defining the door's position and size.
     * @param p_destination The destination that the door leads to.
     */
    Door(Rectangle p_r, std::string p_destination) :
        Rectangle(p_r.getLeft() * globals::SPRITE_SCALE,
                  p_r.getTop() * globals::SPRITE_SCALE,
                  p_r.getWidth() * globals::SPRITE_SCALE,
                  p_r.getHeight() * globals::SPRITE_SCALE),
        _destination(p_destination)
    {}

    /**
     * @brief Gets the rectangle representing the door's position and size.
     * 
     * @return Rectangle: The rectangle of the door.
     */
    const inline Rectangle getRectangle() const { return this->getRect(); }

    /**
     * @brief Gets the destination that the door leads to.
     * 
     * @return std::string: The destination of the door.
     */
    const inline std::string getDestination() const { return this->_destination; }

private:
    std::string _destination; ///< The destination that the door leads to.
};

#endif /* DOOR */