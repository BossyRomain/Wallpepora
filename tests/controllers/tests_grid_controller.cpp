#include <gtest/gtest.h>
#include "controllers/grid_controller.hpp"
#include "controllers/images_controller.hpp"
#include "fixtures.hpp"

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

/**
 * Checks :
 * - tiles are cutted or deleted if needed when updating the number of rows of the grid
 */
TEST(TestsGridController, TestsTilesRowsUpdate) {
    GridController controller;

    int id = controller.merge(0, 0, 2, 2);
    controller.setRowsCount(1);

    const Tile *p_tile = controller.getTile(id);
    ASSERT_EQ(p_tile->getRowMax(), 0);
    ASSERT_EQ(p_tile->getHeight(), 1);
    ASSERT_EQ(p_tile->getColMax(), 2);
    ASSERT_EQ(p_tile->getWitdh(), 3);

    controller.unmerge(id);
    controller.setRowsCount(10);
    id = controller.merge(8, 8, 9, 9);
    ASSERT_TRUE(controller.getTile(id) != nullptr);

    controller.setRowsCount(5);
    ASSERT_TRUE(controller.getTile(id) == nullptr);
}

/**
 * Checks :
 * - tiles are cutted or deleted if needed when updating the number of columns of the grid
 */
TEST(TestsGridController, TestsTilesColsUpdate) {
    GridController controller;

    int id = controller.merge(0, 0, 2, 2);
    controller.setColsCount(1);

    const Tile *p_tile = controller.getTileAt(0, 0);
    ASSERT_EQ(p_tile->getColMax(), 0);
    ASSERT_EQ(p_tile->getWitdh(), 1);
    ASSERT_EQ(p_tile->getRowMax(), 2);
    ASSERT_EQ(p_tile->getHeight(), 3);

    controller.unmerge(id);
    controller.setColsCount(10);
    id = controller.merge(8, 8, 9, 9);
    ASSERT_TRUE(controller.getTile(id) != nullptr);

    controller.setColsCount(5);
    ASSERT_TRUE(controller.getTile(id) == nullptr);
}

/**
 * Checks :
 * - case when it is possible to merge cells into tile
 * - case when it is impossible to merge cells into tile
 */
TEST(TestsGridController, TestsCellsMerging) {
    GridController controller;

    int id = controller.merge(0, 0, 2, 2);
    ASSERT_NE(id, -1);

    id = controller.merge(0, 0, 2, 1);
    ASSERT_EQ(id, -1);
}

/**
 * Checks :
 * - case when it is possible to unmerge tiles
 * - case when it is impossible to unmerge tiles
 */
TEST(TestsGridController, TestsCellsUnmerging) {
    GridController controller;

    int id = controller.merge(0, 0, 2, 2);
    
    try {
        controller.unmerge(id);
    } catch(std::out_of_range& e) {
        FAIL();
    }

    try {
        controller.unmerge(id);
        FAIL();
    } catch(std::out_of_range& e) {
    }
}

/**
 * Checks :
 * - it is possible to place images in cells
 * - it is possible to place images in tiles
 */
TEST_F(TestsImagesPaths, TestsImagesPlacing) {
    GridController gridController;
    ImagesController imagesController;

    imagesController.load(getValidsImagesPaths());

    // Placing an image in a cell
    gridController.placeImage(0, 0, imagesController.getImage(0));
    
    Tile tile = gridController.getTiles()[0];
    ASSERT_EQ(tile.getRowMin(), 0);
    ASSERT_EQ(tile.getColMin(), 0);
    ASSERT_EQ(tile.getWitdh(), 1);
    ASSERT_EQ(tile.getHeight(), 1);
    ASSERT_EQ(tile.getImage(), imagesController.getImage(0));

    // Placing an image in a tile
    int id = gridController.merge(1, 1, gridController.getRowsCount() - 1, gridController.getColsCount() - 1);
    gridController.placeImage(id, imagesController.getImage(3));
    
    const Tile *p_tile = gridController.getTile(id);
    ASSERT_EQ(p_tile->getImage(), imagesController.getImage(3));
}