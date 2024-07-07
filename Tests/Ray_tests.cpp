#include <gtest/gtest.h>

#include "Ray.h"

/**
 * @brief Tests the construction of a Ray.
 */
TEST(RayTest, Constructor)
{
    Point start_point(1, 2);
    Vector direction(3, 4);
    Ray ray(start_point, direction);
    EXPECT_DOUBLE_EQ(ray.start_point.x, 1);
    EXPECT_DOUBLE_EQ(ray.start_point.y, 2);
    EXPECT_DOUBLE_EQ(ray.direction.x, 3);
    EXPECT_DOUBLE_EQ(ray.direction.y, 4);
}

/**
 * @brief Tests if a point is on the ray.
 */
TEST(RayTest, PointOnRay)
{
    Point start_point(1, 1);
    Vector direction(2, 2);
    Ray ray(start_point, direction);

    Point point_on_ray(3, 3);
    Point point_not_on_ray(2, 3);
    Point point_behind_ray(0, 0);

    EXPECT_TRUE(ray.is_point_on_ray(point_on_ray));
    EXPECT_FALSE(ray.is_point_on_ray(point_not_on_ray));
    EXPECT_FALSE(ray.is_point_on_ray(point_behind_ray));
}