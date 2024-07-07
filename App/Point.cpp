#include "Point.h"

Point::Point(double x, double y) : x(x), y(y) {}

Vector Point::operator-(const Point &other) const
{
    return Vector(x - other.x, y - other.y);
}

Point Point::operator+(const Vector &vec) const
{
    return Point(x + vec.x, y + vec.y);
}

bool Point::operator==(const Point &other) const
{
    return x == other.x && y == other.y;
}
