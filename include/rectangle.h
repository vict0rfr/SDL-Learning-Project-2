#ifndef RECTANGLE
#define RECTANGLE

#include "globals.h"

class Rectangle{
    public:
        Rectangle(){}
        Rectangle(int p_x, int p_y, int p_width, int p_height):
            _x(p_x),
            _y(p_y),
            _width(p_width),
            _height(p_height)
        {}

        int getCenterX() const{ return this->_x + _width / 2; }
        int getCenterY() const{ return this->_y + _width / 2; }

        int getLeft() const{ return this->_x; }
        int getRight() const{ return this->_x + this->_width; }
        int getTop() const{ return this->_y; }
        int getBottom() const{ return this->_y + this->_height; }

        int getWidth() const{ return this->_width; }
        int getHeight() const{ return this->_height; }

        int getSide(const sides::Side p_side) const{
            return
                    p_side == sides::LEFT ? this->getLeft() :
                    p_side == sides::RIGHT ? this->getRight() :
                    p_side == sides::BOTTOM ? this->getBottom() :
                    p_side == sides::TOP ? this->getTop() :
                    sides::NONE;

        }

        //method takes a param (which is another rectangle) to check
        //if they both collide
        bool collidesWith(const Rectangle &p_other) const{
            return
                    this->getRight() >= p_other.getLeft() &&
                    this->getLeft() <= p_other.getRight() &&
                    this->getTop() <= p_other.getBottom() &&
                    this->getBottom() >= p_other.getTop();
        }

        bool isValidRectangle() const{
            return (this->_x >= 0 && this->_y >= 0 && this->_width >= 0 && this->_height >= 0);
        }

        const inline Rectangle getRect() const { return *this; }

    private:
        int _x, _y, _width, _height;
};

#endif /* RECTANGLE */
