#include "Ray.h"

#include <cmath>

Ray::Ray(const Point &start_point, const Vector &direction)
    : start_point(start_point), direction(direction) {}

bool Ray::is_point_on_ray(const Point &point, double EPS) const
{
    // Vector from start point to the point
    Vector to_point = point - start_point;

    // Check if the cross product is close to zero (collinear)
    if (std::abs(direction.cross_product(to_point)) > EPS)
        return false;

    // Check if the dot product is non-negative (same direction)
    if (direction.dot_product(to_point) < -EPS)
        return false;

    return true;
}