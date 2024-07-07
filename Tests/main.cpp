#include <gtest/gtest.h>

/**
 * @brief Main function for running all the tests.
 * @param argc Number of command line arguments.
 * @param argv Command line arguments.
 * @return Exit status.
 */
int main(int argc, char **argv)
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}