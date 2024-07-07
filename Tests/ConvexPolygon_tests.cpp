#include <gtest/gtest.h>

#include "ConvexPolygon.h"

/**
 * @brief Tests if a set of points forms a convex polygon.
 */
TEST(ConvexPolygonTest, IsConvex)
{
    try
    {
        std::vector<Point> points = {
            Point(0, 0), 
            Point(1, 0), 
            Point(1, 1), 
            Point(0, 1)
        };
        ConvexPolygon polygon(points.begin(), points.end());
        SUCCEED();
    }
    catch(std::invalid_argument)
    {
        FAIL();
    }
}

/**
 * @brief Tests if a set of points doesn't form a convex polygon.
 */
TEST(ConvexPolygonTest, IsNotConvex)
{
    try
    {
        std::vector<Point> points = {
            Point(0, 0), 
            Point(1, 1), 
            Point(1, 0), 
            Point(0, 1)
        };
        ConvexPolygon polygon(points.begin(), points.end());
        FAIL();
    }
    catch(std::invalid_argument)
    {
        SUCCEED();
    }
}

void checkAxes(
    std::vector<std::pair<Point, Point>>& expectedAxes, 
    std::vector<Ray>& axes)
{
    for (const auto& expectedAxis : expectedAxes)
    {
        bool axisFound = false;

        for (const auto& axis : axes)
        {
            if (axis.is_point_on_ray(expectedAxis.first, 1e-9)
                && axis.is_point_on_ray(expectedAxis.second, 1e-9))
            {
                axisFound = true;
                break;
            }
        }

        EXPECT_TRUE(axisFound);
    }
}

/**
 * @brief Tests finding axes of symmetry for a convex polygon.
 */
TEST(ConvexPolygonTest, FindAxesOfSymmetry1)
{
    std::vector<Point> points = {
        Point(0, 0), 
        Point(1, 0), 
        Point(1, 1), 
        Point(0, 1)
    };
    std::vector<std::pair<Point, Point>> expectedAxes = {
        {Point(0, 0), Point(1, 1)},
        {Point(1, 0), Point(0, 1)},
        {Point(0.5, 0), Point(0.5, 1)},
        {Point(0, 0.5), Point(1, 0.5)},
    };

    ConvexPolygon polygon(points.begin(), points.end());
    
    auto axes = polygon.find_axes_of_symmetry();
    EXPECT_EQ(axes.size(), 4);

    checkAxes(expectedAxes, axes);
}

/**
 * @brief Tests finding axes of symmetry for a convex polygon.
 */
TEST(ConvexPolygonTest, FindAxesOfSymmetry2)
{
    std::vector<Point> points = {
        Point(0, 0), 
        Point(2, 1), 
        Point(0, 3), 
        Point(-2, 1),
    };
    std::vector<std::pair<Point, Point>> expectedAxes = {
        {Point(0, 0), Point(0, 3)},
    };
    ConvexPolygon polygon(points.begin(), points.end());
    auto axes = polygon.find_axes_of_symmetry();
    EXPECT_EQ(axes.size(), 1);

    checkAxes(expectedAxes, axes);
}

/**
 * @brief Tests finding axes of symmetry for a convex polygon.
 */
TEST(ConvexPolygonTest, FindAxesOfSymmetry3)
{

    std::vector<Point> points = {
        Point(0.1, 1.0),
        Point(-1.0, 0.0),
        Point(0.0, -1.0),
        Point(1.0, -0.5),
        Point(2.0, 1.0),
    };
    ConvexPolygon polygon(points.begin(), points.end());
    auto axes = polygon.find_axes_of_symmetry();
    EXPECT_EQ(axes.size(), 0);
}
