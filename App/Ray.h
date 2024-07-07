#pragma once

#include "Point.h"
#include "Vector.h"

/**
 * @class Ray
 * @brief Represents a ray in 2D space.
 */
class Ray
{
public:
    /**
     * @brief Constructs a Ray with a starting point and a direction vector.
     * @param start_point The starting point of the ray.
     * @param direction The direction vector of the ray.
     */
    Ray(const Point &start_point, const Vector &direction);

    /**
     * @brief Checks if a given point is on the ray.
     * @param point The point to check.
     * @param EPS Tolerance for floating point comparisons.
     * @return True if the point is on the ray, false otherwise.
     */
    bool is_point_on_ray(const Point &point, double EPS = EPS_DEFAULT) const;

    Point start_point; ///< Starting point of the ray.
    Vector direction; ///< Direction vector of the ray.
};

