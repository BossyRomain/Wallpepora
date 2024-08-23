#include <gtest/gtest.h>
#include "controllers/grid_controller.hpp"

/**
 * Checks :
 * - it possible to change the number of rows of the grid
 * - the grid always has at least one 1 row
 */
TEST(TestsGridController, TestsRowsUpdate) {
    GridController controller;

    // Valid update
    ASSERT_TRUE(controller.setRowsCount(5));
    ASSERT_EQ(controller.getRowsCount(), 5);

    // Invalid update
    ASSERT_FALSE(controller.setRowsCount(-1));
    ASSERT_EQ(controller.getRowsCount(), 5);
}

/**
 * Checks :
 * - it possible to change the number of columns of the grid
 * - the grid always has at least one 1 column
 */
TEST(TestsGridController, TestsColsUpdate) {
    GridController controller;

    // Valid update
    ASSERT_TRUE(controller.setColsCount(5));
    ASSERT_EQ(controller.getColsCount(), 5);

    // Invalid update
    ASSERT_FALSE(controller.setColsCount(-1));
    ASSERT_EQ(controller.getColsCount(), 5);
}

/**
 * Checks :
 * - it possible to change the cells'size of the grid
 * - the cells always have a size of 20 pixels at least
 */
TEST(TestsGridController, TestsCellsSizeUpdate) {
    GridController controller;

    // Valid update
    ASSERT_TRUE(controller.setCellsSize(78));
    ASSERT_EQ(controller.getCellsSize(), 78);

    // Invalid update
    ASSERT_FALSE(controller.setCellsSize(19));
    ASSERT_EQ(controller.getCellsSize(), 78);
}