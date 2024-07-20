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

Point Ray::reflect_point(const Point &point, double EPS) const
{
    // Normalize the direction vector of the ray
    Vector normalized_direction = direction;
    double length = std::sqrt(
        normalized_direction.x * normalized_direction.x 
        + normalized_direction.y * normalized_direction.y);
    normalized_direction.x /= length;
    normalized_direction.y /= length;

    // Compute the dot product of the point and the ray direction
    double dot = 
        (point.x - start_point.x) * normalized_direction.x 
        + (point.y - start_point.y) * normalized_direction.y;

    // Compute the projection of the point onto the ray
    Point projection(
        start_point.x + dot * normalized_direction.x,
        start_point.y + dot * normalized_direction.y
    );

    // Reflect the point across the projection
    return Point(
        2 * projection.x - point.x,
        2 * projection.y - point.y
    );
}