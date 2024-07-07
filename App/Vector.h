#pragma once

/**
 * @class Vector
 * @brief Represents a 2D vector.
 */
class Vector
{
public:
    /**
     * @brief Constructs a Vector with given x and y components.
     * @param x X component of the vector.
     * @param y Y component of the vector.
     */
    Vector(double x, double y);

    /**
     * @brief Computes the dot product of this vector and another vector.
     * @param other The other vector.
     * @return The dot product.
     */
    double dot_product(const Vector &other) const;

    /**
     * @brief Computes the cross product of this vector and another vector.
     * @param other The other vector.
     * @return The cross product.
     */
    double cross_product(const Vector &other) const;

    /**
     * @brief Checks if this vector is equal to another vector.
     * @param other The other vector.
     * @return True if the vectors are equal, false otherwise.
     */
    bool operator==(const Vector &other) const;

    double x; ///< X component of the vector.
    double y; ///< Y component of the vector.
};