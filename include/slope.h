#ifndef SLOPE
#define SLOPE

#include "globals.h"
#include "rectangle.h"
#include <cmath> // Include the <cmath> header for sqrt function

class Slope{
    public:
        Slope(){}
        Slope(Vector2f p_p1, Vector2f p_p2):_p1(p_p1), _p2(p_p2){
            if (this->_p2.x - this->_p1.x != 0 || this->_p2.y - this->_p1.y != 0) {
            _slope = (fabs(this->_p2.y) - fabs(this->_p1.y)) / (fabs(this->_p2.x) - fabs(this->_p1.x));
            }
        }

        inline float getSlope() const{
            return this->_slope;
        }

        bool collidesWith(const Rectangle &p_other) const{
            return
                    (p_other.getRight() >= this->_p2.x &&
                    p_other.getLeft() <= this->_p1.x &&
                    p_other.getTop() <= this->_p2.y &&
                    p_other.getBottom() >= this->_p1.y) ||
                    (p_other.getRight() >= this->_p1.x &&
                    p_other.getLeft() <= this->_p2.x &&
                    p_other.getTop() <= this->_p1.y &&
                    p_other.getBottom() >= this->_p2.y) ||
                    (p_other.getLeft() <= this->_p1.x &&
                    p_other.getRight() >= this->_p2.x &&
                    p_other.getTop() <= this->_p1.y &&
                    p_other.getBottom() >= this->_p2.y) ||
                    (p_other.getLeft() <= this->_p2.x &&
                    p_other.getRight() >= this->_p1.x &&
                    p_other.getTop() <= this->_p2.y &&
                    p_other.getBottom() >= this->_p1.y);
        }

        const inline Vector2f getP1() const{
            return this->_p1;
        }

        const inline Vector2f getP2() const{
            return this->_p2;
        }
    private:
        Vector2f _p1, _p2;
        float _slope;
};

#endif /* SLOPE */
