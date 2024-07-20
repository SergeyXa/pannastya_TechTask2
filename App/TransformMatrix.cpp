#include "TransformMatrix.h"

#include <cmath>
#include <stdexcept>

TransformMatrix::TransformMatrix()
{
    for (int i = 0; i < 3; ++i)
        for (int j = 0; j < 3; ++j)
            data[i][j] = (i == j) ? 1.0 : 0.0;
}

TransformMatrix::TransformMatrix(const Ray &x_axis, const Ray &y_axis)
{
    data[0][0] = x_axis.direction.x;
    data[0][1] = y_axis.direction.x;
    data[0][2] = x_axis.start_point.x;
    data[1][0] = x_axis.direction.y;
    data[1][1] = y_axis.direction.y;
    data[1][2] = x_axis.start_point.y;
    data[2][0] = 0.0;
    data[2][1] = 0.0;
    data[2][2] = 1.0;
}

TransformMatrix TransformMatrix::operator*(const TransformMatrix &other) const
{
    TransformMatrix result;
    for (int i = 0; i < 3; ++i)
    {
        for (int j = 0; j < 3; ++j)
        {
            result.data[i][j] = 0.0;
            for (int k = 0; k < 3; ++k)
            {
                result.data[i][j] += data[i][k] * other.data[k][j];
            }
        }
    }
    return result;
}

Point TransformMatrix::operator*(const Point &point) const
{
    double x = data[0][0] * point.x + data[0][1] * point.y + data[0][2];
    double y = data[1][0] * point.x + data[1][1] * point.y + data[1][2];
    return Point(x, y);
}

void TransformMatrix::set_translation(double dx, double dy)
{
    *this = TransformMatrix();
    data[0][2] = dx;
    data[1][2] = dy;
}

void TransformMatrix::set_rotation(double angle)
{
    *this = TransformMatrix();
    data[0][0] = std::cos(angle);
    data[0][1] = -std::sin(angle);
    data[1][0] = std::sin(angle);
    data[1][1] = std::cos(angle);
}

void TransformMatrix::set_scaling(double sx, double sy)
{
    *this = TransformMatrix();
    data[0][0] = sx;
    data[1][1] = sy;
}

TransformMatrix TransformMatrix::inverse() const
{
    if (data[2][0] == 0.0
     && data[2][1] == 0.0
     && data[2][2] == 1.0)
    {
        double det = data[0][0] * data[1][1] - data[0][1] * data[1][0];
        if (det == 0)
            throw std::runtime_error("Matrix is singular and cannot be inverted.");

        double inv_det = 1.0 / det;

        TransformMatrix result;
        result.data[0][0] = data[1][1] * inv_det;
        result.data[0][1] = -data[0][1] * inv_det;
        result.data[0][2] = (data[0][1] * data[1][2] - data[0][2] * data[1][1]) * inv_det;

        result.data[1][0] = -data[1][0] * inv_det;
        result.data[1][1] = data[0][0] * inv_det;
        result.data[1][2] = (data[0][2] * data[1][0] - data[0][0] * data[1][2]) * inv_det;

        result.data[2][0] = 0.0;
        result.data[2][1] = 0.0;
        result.data[2][2] = 1.0;

        return result;
    }

    TransformMatrix result;
    double det = determinant();

    if (det == 0)
        throw std::runtime_error("Matrix is singular and cannot be inverted.");

    double inv_det = 1.0 / det;

    result.data[0][0] = (data[1][1] * data[2][2] - data[1][2] * data[2][1]) * inv_det;
    result.data[0][1] = (data[0][2] * data[2][1] - data[0][1] * data[2][2]) * inv_det;
    result.data[0][2] = (data[0][1] * data[1][2] - data[0][2] * data[1][1]) * inv_det;

    result.data[1][0] = (data[1][2] * data[2][0] - data[1][0] * data[2][2]) * inv_det;
    result.data[1][1] = (data[0][0] * data[2][2] - data[0][2] * data[2][0]) * inv_det;
    result.data[1][2] = (data[0][2] * data[1][0] - data[0][0] * data[1][2]) * inv_det;

    result.data[2][0] = (data[1][0] * data[2][1] - data[1][1] * data[2][0]) * inv_det;
    result.data[2][1] = (data[0][1] * data[2][0] - data[0][0] * data[2][1]) * inv_det;
    result.data[2][2] = (data[0][0] * data[1][1] - data[0][1] * data[1][0]) * inv_det;

    return result;
}

double TransformMatrix::determinant() const
{
    return data[0][0] * (data[1][1] * data[2][2] - data[1][2] * data[2][1]) -
           data[0][1] * (data[1][0] * data[2][2] - data[1][2] * data[2][0]) +
           data[0][2] * (data[1][0] * data[2][1] - data[1][1] * data[2][0]);
}
