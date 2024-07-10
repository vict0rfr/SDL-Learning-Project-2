#ifndef SLOPE
#define SLOPE

#include "globals.h"
#include "rectangle.h"
#include <cmath> // Include the <cmath> header for sqrt function

/**
 * @class Slope
 * @brief Represents a slope defined by two points.
 * 
 * The Slope class provides methods to calculate the slope between two points
 * and check for collisions with a rectangle.
 */
class Slope {
public:
    /**
     * @brief Default constructor for the Slope class.
     */
    Slope() {}

    /**
     * @brief Constructs a Slope with two points.
     * 
     * This constructor initializes the slope using two points and calculates
     * the slope value.
     * 
     * @param p_p1 The first point.
     * @param p_p2 The second point.
     */
    Slope(Vector2f p_p1, Vector2f p_p2) : _p1(p_p1), _p2(p_p2) {
        if (this->_p2.x - this->_p1.x != 0 || this->_p2.y - this->_p1.y != 0) {
            _slope = (fabs(this->_p2.y) - fabs(this->_p1.y)) / (fabs(this->_p2.x) - fabs(this->_p1.x));
        }
    }

    /**
     * @brief Gets the slope value.
     * 
     * This method returns the calculated slope value.
     * 
     * @return float: The slope value.
     */
    inline float getSlope() const {
        return this->_slope;
    }

    /**
     * @brief Checks for collision with a rectangle.
     * 
     * This method checks if the slope collides with the given rectangle.
     * 
     * @param p_other The rectangle to check collision against.
     * @return bool: True if there is a collision, false otherwise.
     */
    bool collidesWith(const Rectangle &p_other) const {
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

    /**
     * @brief Gets the first point of the slope.
     * 
     * This method returns the first point used to define the slope.
     * 
     * @return const Vector2f: The first point.
     */
    const inline Vector2f getP1() const {
        return this->_p1;
    }

    /**
     * @brief Gets the second point of the slope.
     * 
     * This method returns the second point used to define the slope.
     * 
     * @return const Vector2f: The second point.
     */
    const inline Vector2f getP2() const {
        return this->_p2;
    }

private:
    Vector2f _p1, _p2; ///< The two points defining the slope.
    float _slope; ///< The calculated slope value.
};

#endif /* SLOPE */