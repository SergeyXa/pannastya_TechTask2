#include "Vector.h"

Vector::Vector(double x, double y) : x(x), y(y) {}

double Vector::dot_product(const Vector &other) const
{
    return x * other.x + y * other.y;
}

double Vector::cross_product(const Vector &other) const
{
    return x * other.y - y * other.x;
}

bool Vector::operator==(const Vector &other) const
{
    return x == other.x && y == other.y;
}
