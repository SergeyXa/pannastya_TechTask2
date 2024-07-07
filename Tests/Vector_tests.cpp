#include <gtest/gtest.h>

#include "Vector.h"

/**
 * @brief Tests the dot product of two vectors.
 */
TEST(VectorTest, DotProduct)
{
    Vector v1(3, 4);
    Vector v2(1, 2);
    EXPECT_DOUBLE_EQ(v1.dot_product(v2), 11);
}

/**
 * @brief Tests the cross product of two vectors.
 */
TEST(VectorTest, CrossProduct)
{
    Vector v1(3, 4);
    Vector v2(1, 2);
    EXPECT_DOUBLE_EQ(v1.cross_product(v2), 2);
}

/**
 * @brief Tests the equality operator for vectors.
 */
TEST(VectorTest, Equality)
{
    Vector v1(3, 4);
    Vector v2(3, 4);
    Vector v3(1, 2);
    EXPECT_TRUE(v1 == v2);
    EXPECT_FALSE(v1 == v3);
}
