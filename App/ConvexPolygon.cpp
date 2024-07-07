#include "ConvexPolygon.h"

#include "TransformMatrix.h"

#include <algorithm>
#include <cmath>
#include <stdexcept>

bool ConvexPolygon::is_convex() const
{
    if (points.size() < 3) return false;

    bool sign = false;
    for (size_t i = 0; i < points.size(); ++i)
    {
        const Point &p0 = points[i];
        const Point &p1 = points[(i + 1) % points.size()];
        const Point &p2 = points[(i + 2) % points.size()];

        Vector v1 = p1 - p0;
        Vector v2 = p2 - p1;

        double cross_product = v1.cross_product(v2);
        if (i == 0)
        {
            sign = cross_product > 0;
        }
        else if ((cross_product > 0) != sign)
        {
            return false;
        }
    }
    return true;
}

std::vector<Ray> ConvexPolygon::find_axes_of_symmetry(double EPS) const
{
    std::vector<Ray> result;

    const auto n = points.size();
    const auto half_n = (n + 1) / 2;

    auto get_midpoint =
        [](const Point &a, const Point &b) -> Point
    {
        return Point(
            (a.x + b.x) / 2,
            (a.y + b.y) / 2);
    };

    auto is_axis_symmetric =
        [&](Ray axis,
            size_t index_of_next_point_in_forward_direction,
            size_t index_of_next_point_in_reverse_direction) -> bool
    {
        auto axis_perpendicular_direction =
            Vector(-axis.direction.y, axis.direction.x);

        Ray axis2(
            axis.start_point, axis_perpendicular_direction);

        auto axis_transform =
            TransformMatrix(axis, axis2)
            .inverse();

        auto &fi = index_of_next_point_in_forward_direction;
        auto &ri = index_of_next_point_in_reverse_direction;

        for (size_t j = 0; j < half_n; ++j)
        {
            if (fi == n) fi -= n;
            if (ri == (size_t)-1) ri = n - 1;

            if (fi != ri)
            {
                auto ftp =
                    // forward direction transformed point
                    axis_transform * points[fi];

                auto rtp =
                    // reverse direction transformed point
                    axis_transform * points[ri];

                if (std::abs(ftp.x - rtp.x) > EPS
                    || std::abs(ftp.y) - std::abs(rtp.y) > EPS)
                    return false;
            }

            fi++;
            ri--;
        }

        return true;
    };

    bool has_even_points_amount = n % 2 == 0;

    for (size_t i = 0; i < half_n; ++i)
    {
        auto io =
            // index of a point that's
            // assumed to be an opposite one
            // if the polygon is symmetrical
            i + half_n;

        const auto &p = points[i];
        const auto &q = points[i + 1];
        auto m = get_midpoint(p, q);

        if (has_even_points_amount)
        {
            const auto &po = points[io];
            const auto &qo = points[(io + 1) % n];
            auto mo = get_midpoint(po, qo);

            // Checking if symmetry lies through 
            // the current point and opposite point
            {
                Ray axis(p, po - p);

                if (is_axis_symmetric(axis, i + 1, i - 1))
                    result.push_back(axis);
            }

            // Checking if symmetry lies through 
            // the midpoint of the current segment, 
            // and opposite midpoint
            {
                Ray axis(m, mo - m);

                if (is_axis_symmetric(axis, i + 1, i))
                    result.push_back(axis);
            }
        }
        else // !has_even_points_amount
        {
            const auto &po = points[io % n];
            const auto &qo = points[io - 1];
            auto mo = get_midpoint(po, qo);

            // Checking if symmetry lies through 
            // the current point and opposite midpoint
            {
                Ray axis(p, mo - p);

                if (is_axis_symmetric(axis, i + 1, i - 1))
                    result.push_back(axis);
            }

            // Checking if symmetry lies through 
            // the midpoint of the current segment, 
            // and opposite point
            {
                Ray axis(m, po - m);

                if (is_axis_symmetric(axis, i + 1, i))
                    result.push_back(axis);
            }
        }
    }

    return result;
}
