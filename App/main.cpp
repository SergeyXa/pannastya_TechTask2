#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include "ConvexPolygon.h"

/**
 * @brief Reads points from a text file.
 * @param filename The name of the text file.
 * @return A vector of points read from the file.
 * @throws std::runtime_error if the file cannot be opened or if the point 
 *         format is invalid.
 */
std::vector<Point> read_points_from_file(const std::string &filename)
{
    std::vector<Point> points;
    std::ifstream file(filename);

    if (!file.is_open())
    {
        throw std::runtime_error("Unable to open file.");
    }

    std::string line;
    while (std::getline(file, line))
    {
        std::istringstream iss(line);
        double x, y;
        if (!(iss >> x >> y))
        {
            throw std::runtime_error("Invalid point format in file.");
        }
        points.emplace_back(x, y);
    }

    return points;
}

/**
 * @brief Main function for the console application.
 * @param argc Number of command line arguments.
 * @param argv Command line arguments.
 * @return Exit status.
 */
int main(int argc, char *argv[])
{
    if (argc != 2)
    {
        std::cerr << "Usage: " << argv[0]
                  << " <filename>" << std::endl;
        return EXIT_FAILURE;
    }

    try
    {
        std::vector<Point> points =
            read_points_from_file(argv[1]);

        ConvexPolygon polygon(points.begin(), points.end());

        std::vector<Ray> axes =
            polygon.find_axes_of_symmetry();

        if (axes.empty())
        {
            std::cout << "The polygon is non-symmetric." << std::endl;
        }
        else
        {
            std::cout << "Axes of symmetry:" << std::endl;
            for (const auto &axis : axes)
            {
                std::cout
                    << axis.start_point.x << ' '
                    << axis.start_point.y << ' '
                    << "- "
                    << axis.start_point.x + axis.direction.x << ' '
                    << axis.start_point.y + axis.direction.y << std::endl;
            }
        }
    }
    catch (const std::exception &e)
    {
        std::cerr << "Error: " << e.what() << std::endl;
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}
