#pragma once

#include "Point.h"
#include "Ray.h"

/**
 * @class TransformMatrix
 * @brief Represents a 3x3 matrix for 2D coordinate transformations.
 *        The matrix is in row-major form.
 */
class TransformMatrix
{
public:
    /**
     * @brief Constructs a 3x3 identity matrix.
     */
    TransformMatrix();

    /**
     * @brief Constructs a 3x3 matrix for coordinate transformation using
     *        given x and y axes defined by rays.
     * @param x_axis The ray defining the x axis.
     * @param y_axis The ray defining the y axis.
     */
    TransformMatrix(const Ray &x_axis, const Ray &y_axis);

    /**
     * @brief Multiplies this matrix by another 3x3 matrix.
     * @param other The other matrix.
     * @return The product matrix.
     */
    TransformMatrix operator*(const TransformMatrix &other) const;

    /**
     * @brief Transforms a point using this matrix.
     * @param point The point to transform.
     * @return The transformed point.
     */
    Point operator*(const Point &point) const;

    /**
     * @brief Sets this matrix as a translation matrix.
     * @param dx Translation in the x direction.
     * @param dy Translation in the y direction.
     */
    void set_translation(double dx, double dy);

    /**
     * @brief Sets this matrix as a rotation matrix.
     * @param angle Rotation angle in radians.
     */
    void set_rotation(double angle);

    /**
     * @brief Sets this matrix as a scaling matrix.
     * @param sx Scaling factor in the x direction.
     * @param sy Scaling factor in the y direction.
     */
    void set_scaling(double sx, double sy);

    /**
     * @brief Computes the inverse of this matrix.
     * @return The inverse matrix.
     * @throws std::runtime_error if the matrix is singular.
     */
    TransformMatrix inverse() const;

private:
    /**
     * @brief Computes the determinant of this matrix.
     * @return The determinant value.
     */
    double determinant() const;

    double data[3][3]; ///< Matrix elements in row-major form.
};
