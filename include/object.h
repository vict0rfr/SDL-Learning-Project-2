#ifndef OBJECT
#define OBJECT

#include "rectangle.h"

class Object : public Rectangle {
public:
    Object(Rectangle p_r) : 
        Rectangle(p_r.getLeft() * globals::SPRITE_SCALE,
                  p_r.getTop() * globals::SPRITE_SCALE,
                  p_r.getWidth() * globals::SPRITE_SCALE,
                  p_r.getHeight() * globals::SPRITE_SCALE),
        _isActive(false)
    {}

    const inline bool getActive() const { return this->_isActive; }

private:
    bool _isActive; ///< True if the player still hasn't used this object, (meaning it's still on the map).
};

#endif /* OBJECT */
