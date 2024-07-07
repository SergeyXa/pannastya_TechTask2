#pragma once

#include "Vector.h"

/**
 * @class Point
 * @brief Represents a point in 2D space.
 */
class Point
{
public:
    /**
     * @brief Constructs a Point with given x and y coordinates.
     * @param x X coordinate of the point.
     * @param y Y coordinate of the point.
     */
    Point(double x, double y);

    /**
     * @brief Subtracts another point from this point, returning the 
     *        resulting vector.
     * @param other The other point.
     * @return The resulting vector.
     */
    Vector operator-(const Point &other) const;

    /**
     * @brief Adds a vector to this point, returning the resulting point.
     * @param vec The vector to add.
     * @return The resulting point.
     */
    Point operator+(const Vector &vec) const;

    /**
     * @brief Checks if this point is equal to another point.
     * @param other The other point.
     * @return True if the points are equal, false otherwise.
     */
    bool operator==(const Point &other) const;

    double x; ///< X coordinate of the point.
    double y; ///< Y coordinate of the point.
};

