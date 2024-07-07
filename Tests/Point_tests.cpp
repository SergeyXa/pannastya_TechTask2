#include <gtest/gtest.h>

#include "Point.h"

/**
 * @brief Tests the subtraction of two points, resulting in a vector.
 */
TEST(PointTest, Subtraction)
{
    Point p1(3, 4);
    Point p2(1, 2);
    Vector v = p1 - p2;
    EXPECT_DOUBLE_EQ(v.x, 2);
    EXPECT_DOUBLE_EQ(v.y, 2);
}

/**
 * @brief Tests the addition of a vector to a point, resulting in a new point.
 */
TEST(PointTest, Addition)
{
    Point p(1, 2);
    Vector v(3, 4);
    Point result = p + v;
    EXPECT_DOUBLE_EQ(result.x, 4);
    EXPECT_DOUBLE_EQ(result.y, 6);
}

/**
 * @brief Tests the equality operator for points.
 */
TEST(PointTest, Equality)
{
    Point p1(1, 2);
    Point p2(1, 2);
    Point p3(3, 4);
    EXPECT_TRUE(p1 == p2);
    EXPECT_FALSE(p1 == p3);
}
