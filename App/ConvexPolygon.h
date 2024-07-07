#pragma once

#include "Point.h"
#include "Ray.h"

#include <iterator>
#include <stdexcept>
#include <vector>

/**
 * @class ConvexPolygon
 * @brief Represents a convex polygon in 2D space.
 */
class ConvexPolygon
{
public:
    /**
     * @brief Constructs a ConvexPolygon from a range of points.
     * @tparam InputIt Iterator type for the input points.
     * @param first Iterator to the first point.
     * @param last Iterator to the past-the-end point.
     * @throws std::invalid_argument if the points do not form a convex polygon.
     */
    template <typename InputIt>
    ConvexPolygon(InputIt first, InputIt last);

    /**
     * @brief Returns an iterator to the beginning of the points vector.
     * @return An iterator to the beginning of the points vector.
     */
    auto begin() const { return points.begin(); }

    /**
     * @brief Returns an iterator to the end of the points vector.
     * @return An iterator to the end of the points vector.
     */
    auto end() const { return points.end(); }

    /**
     * @brief Finds all axes of symmetry for the polygon.
     * @param EPS Tolerance for floating point comparisons.
     * @return A vector of rays defining the axes of symmetry.
     */
    std::vector<Ray> find_axes_of_symmetry(double EPS = EPS_DEFAULT) const;

private:
    std::vector<Point> points;

    /**
     * @brief Checks if the polygon formed by the points is convex.
     * @return True if the polygon is convex, false otherwise.
     */
    bool is_convex() const;
};

template <typename InputIt>
ConvexPolygon::ConvexPolygon(InputIt first, InputIt last)
{
#if __cplusplus > 201703L
    if constexpr (!std::is_same_v<InputIt::value_type, Point>) {
        static_assert(false, "The type of the values passed to the constructor should be Point.");
    }
#endif

    std::copy(first, last, std::back_inserter(points));
    if (!is_convex())
    {
        throw std::invalid_argument(
            "Points do not form a convex polygon."
        );
    }
}
