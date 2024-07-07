#define _USE_MATH_DEFINES

#include <gtest/gtest.h>

#include <cmath>

#include "TransformMatrix.h"

/**
 * @brief Tests the identity transformation matrix.
 */
TEST(TransformMatrixTest, IdentityMatrix)
{
    TransformMatrix matrix;
    Point p(1, 2);
    Point result = matrix * p;
    EXPECT_DOUBLE_EQ(result.x, 1);
    EXPECT_DOUBLE_EQ(result.y, 2);
}

/*!!!
 * @brief Tests the translation transformation matrix.
 */
TEST(TransformMatrixTest, Translation)
{
    TransformMatrix matrix;
    matrix.set_translation(3, 4);
    Point p(1, 2);
    Point result = matrix * p;
    EXPECT_DOUBLE_EQ(result.x, 4);
    EXPECT_DOUBLE_EQ(result.y, 6);
}

/**
 * @brief Tests the rotation transformation matrix.
 */
TEST(TransformMatrixTest, Rotation)
{
    TransformMatrix matrix;
    matrix.set_rotation(M_PI / 2);  // 90 degrees
    Point p(1, 0);
    Point result = matrix * p;
    EXPECT_NEAR(result.x, 0, 1e-9);
    EXPECT_NEAR(result.y, 1, 1e-9);
}

/**
 * @brief Tests the scaling transformation matrix.
 */
TEST(TransformMatrixTest, Scaling)
{
    TransformMatrix matrix;
    matrix.set_scaling(2, 3);
    Point p(1, 1);
    Point result = matrix * p;
    EXPECT_DOUBLE_EQ(result.x, 2);
    EXPECT_DOUBLE_EQ(result.y, 3);
}

/**
 * @brief Tests the inversion of a transformation matrix.
 */
TEST(TransformMatrixTest, Inverse)
{
    TransformMatrix matrix;
    matrix.set_scaling(2, 3);
    TransformMatrix inv_matrix = matrix.inverse();
    Point p(2, 3);
    Point result = inv_matrix * p;
    EXPECT_DOUBLE_EQ(result.x, 1);
    EXPECT_DOUBLE_EQ(result.y, 1);
}
