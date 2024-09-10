#include <gtest/gtest.h>
#include "controllers/grid_controller.hpp"
#include "controllers/images_controller.hpp"
#include "fixtures.hpp"
#include <vector>

/**
 * Tests the update the number of rows of the grid with a valid value.
 */
TEST_F(GridFixture, TestRowsUpdateValid) {
    // Valid update
    int newRows = rand() % 300;
    ASSERT_TRUE(p_gridController->setRowsCount(newRows));
    ASSERT_EQ(p_gridController->getRowsCount(), newRows);
    ASSERT_EQ(p_gridListener->getRowsCount(), newRows);
}

/**
 * Tests the grid can't have less than one row.
 */
TEST_F(GridFixture, TestRowsUpdateInvalid) {
    ASSERT_FALSE(p_gridController->setRowsCount(0));
    ASSERT_NE(p_gridController->getRowsCount(), 0);
    ASSERT_NE(p_gridListener->getRowsCount(), 0);
}

/**
 * Tests the update the number of columns of the grid with a valid value.
 */
TEST_F(GridFixture, TestColsUpdateValid) {
    int newCols = rand() % 300;
    ASSERT_TRUE(p_gridController->setColsCount(newCols));
    ASSERT_EQ(p_gridController->getColsCount(), newCols);
    ASSERT_EQ(p_gridListener->getColsCount(), newCols);
}

/**
 * Tests the grid can't have less than one column.
 */
TEST_F(GridFixture, TestColsUpdateInvalid) {
    ASSERT_FALSE(p_gridController->setColsCount(0));
    ASSERT_NE(p_gridController->getColsCount(), 0);
    ASSERT_NE(p_gridListener->getColsCount(), 0);
}

/**
 * Tests the update of the cells' size of the grid with a valid value.
 */
TEST_F(GridFixture, TestCellsSizeUpdateValid) {
    int size = rand() % 1200;
    ASSERT_TRUE(p_gridController->setCellsSize(size));
    ASSERT_EQ(p_gridController->getCellsSize(), size);
}

/**
 * Tests the cells of the grid can't have a size inferior to 20 pixels.
 */
TEST_F(GridFixture, TestCellsSizeUpdateInvalid) {
    ASSERT_FALSE(p_gridController->setCellsSize(19));
    ASSERT_NE(p_gridController->getCellsSize(), 19);
    ASSERT_NE(p_gridListener->getCellsSize(), 19);
}

/**
 * Tests the tiles on the grid are cut if needed when the update of the grid's number of rows.
 */
TEST_F(GridFixture, TestTilesCutRows) {
    p_gridController->setRowsCount(5);
    p_gridController->setColsCount(5);
    const int newRows = 2;

    int id = p_gridController->merge(0, 3, 3, 3);

    p_gridController->setRowsCount(newRows);

    ASSERT_EQ(p_gridListener->getResizedTiles()[0]->getRowMax(), newRows - 1);
}

/**
 * Tests the tiles on the grid are cut if needed when the update of the grid's number of columns.
 */
TEST_F(GridFixture, TestTilesCutCols) {
    p_gridController->setRowsCount(5);
    p_gridController->setColsCount(5);
    const int newCols = 2;

    int id = p_gridController->merge(0, 0, 0, 3);

    p_gridController->setColsCount(newCols);

    ASSERT_EQ(p_gridListener->getResizedTiles()[0]->getColMax(), newCols - 1);
}

/**
 * Tests the tiles on the grid are deleted if needed when the update of the grid's number of rows.
 */
TEST_F(GridFixture, TestTilesDeletionRows) {
    p_gridController->setRowsCount(5);
    p_gridController->setColsCount(5);
    const int newRows = 2;

    int id = p_gridController->merge(3, 3, 4, 4);

    p_gridController->setRowsCount(newRows);

    ASSERT_EQ(p_gridListener->getDeletedTiles()[0].getId(), id);
}

/**
 * Tests the tiles on the grid are deleted if needed when the update of the grid's number of columns.
 */
TEST_F(GridFixture, TestTilesDeletionCols) {
    p_gridController->setRowsCount(5);
    p_gridController->setColsCount(5);
    const int newCols = 2;

    int id = p_gridController->merge(3, 3, 4, 4);

    p_gridController->setColsCount(newCols);

    ASSERT_EQ(p_gridListener->getDeletedTiles()[0].getId(), id);
}

/**
 * Tests merging cells into a valid tile.
 */
TEST_F(GridFixture, TestCellsMergeValid) {
    p_gridController->setRowsCount(5);
    p_gridController->setColsCount(5);

    const int rowMin = rand() % 3;
    const int colMin = rand() % 3;
    const int rowMax = rand() % 2 + rowMin;
    const int colMax = rand() % 2 + colMin;

    int id = p_gridController->merge(rowMin, colMin, rowMax, colMax);

    ASSERT_GE(id, 0);
    ASSERT_NE(p_gridController->getTile(id), nullptr);

    const Tile *p_tile = p_gridListener->getCreatedTiles()[0];
    ASSERT_EQ(p_tile->getId(), id);
    ASSERT_EQ(p_tile->getRowMin(), rowMin);
    ASSERT_EQ(p_tile->getColMin(), colMin);
    ASSERT_EQ(p_tile->getRowMax(), rowMax);
    ASSERT_EQ(p_tile->getColMax(), colMax);
}

/**
 * Tests merging cells into an invalid tile (tiles collision).
 */
TEST_F(GridFixture, TestCellsMergeInvalidCollision) {
    p_gridController->setRowsCount(5);
    p_gridController->setColsCount(5);

    p_gridController->merge(0, 0, 2, 2);
    ASSERT_EQ(p_gridListener->getCreatedTiles().size(), 1);

    const int rowMin = rand() % 3;
    const int colMin = rand() % 3;
    const int rowMax = rand() % 3 + 2;
    const int colMax = rand() % 3 + 2;

    int id = p_gridController->merge(rowMin, colMin, rowMax, colMax);

    ASSERT_EQ(id, -1);
    ASSERT_EQ(p_gridController->getTile(id), nullptr);

    ASSERT_EQ(p_gridListener->getCreatedTiles().size(), 1);
}

/**
 * Tests merging cells into an invalid tile (coordinates outside the grid).
 */
TEST_F(GridFixture, TestCellsMergeInvalidOutside) {
    p_gridController->setRowsCount(5);
    p_gridController->setColsCount(5);

    int values[4][4] = {
        {-1, 0, 2, 2},
        {0, -1, 2, 2},
        {0, 0, p_gridController->getRowsCount(), 2},
        {0, 0, 2, p_gridController->getColsCount()}
    };

    for(int i = 0; i < 4; i++) {
        int id = p_gridController->merge(values[i][0], values[i][1], values[i][2], values[i][3]);

        ASSERT_EQ(id, -1);
        ASSERT_EQ(p_gridController->getTile(id), nullptr);

        ASSERT_TRUE(p_gridListener->getCreatedTiles().empty());
    }
}

/**
 * Tests that when merge cells into a valid tile, the tile with just one cell that are inside the new tile are destroyed.
 */
TEST_F(GridFixture, TestCellsMergeTilesDeletion) {
    p_gridController->setRowsCount(5);
    p_gridController->setColsCount(5);

    int ids[3];

    for(int i = 0; i < 3; i++) {
        int row = rand() % 5;
        int col = rand() % 5;
        ids[i] = p_gridController->merge(row, col, row, col);
    }

    int id = p_gridController->merge(0, 0, 4, 4);

    ASSERT_EQ(p_gridListener->getDeletedTiles().size(), 3);

    int i = 0;
    for(Tile tile: p_gridListener->getDeletedTiles()) {
        ASSERT_EQ(tile.getId(), ids[i]);
        i++;
    }
}

/**
 * Tests the destruction of a existing tile.
 */
TEST_F(GridFixture, TestTilesDestructionValid) {
    p_gridController->setRowsCount(5);
    p_gridController->setColsCount(5);
    
    const int rowMin = rand() % 3;
    const int colMin = rand() % 3;
    const int rowMax = rand() % 2 + rowMin;
    const int colMax = rand() % 2 + colMin;

    int id = p_gridController->merge(rowMin, colMin, rowMax, colMax);

    p_gridController->unmerge(id);

    ASSERT_FALSE(p_gridListener->getDeletedTiles().empty());
    ASSERT_EQ(p_gridListener->getDeletedTiles()[0].getId(), id);
}

/**
 * Tests the destruction of a non existant tile.
 */
TEST_F(GridFixture, TestTilesDestructionInvalid) {
    EXPECT_THROW(p_gridController->unmerge(0), std::out_of_range);
    EXPECT_THROW(p_gridController->unmerge(-1), std::out_of_range);
}

/**
 * Tests placing an image in a existing tile.
 */
TEST_F(GridFixture, TestImagesPlacingInTiles) {
    p_gridController->setRowsCount(5);
    p_gridController->setColsCount(5);

    int id = p_gridController->merge(0, 0, 4, 4);

    Image img(0, "", cv::Mat());

    p_gridController->placeImage(id, &img);

    const Tile *p_tile = p_gridController->getTile(id);
    ASSERT_EQ(p_tile->getImage(), &img);
    ASSERT_EQ(p_tile->getImage()->getId(), img.getId());

    ASSERT_FALSE(p_gridListener->getPlacedTiles().empty());
    ASSERT_EQ(p_gridListener->getPlacedTiles()[0].second, &img);
    ASSERT_EQ(p_gridListener->getPlacedTiles()[0].second->getId(), img.getId());
}

/**
 * Tests placing an image in a cell which is not in a tile.
 */
TEST_F(GridFixture, TestImagesPlacingInCells) {
    p_gridController->setRowsCount(5);
    p_gridController->setColsCount(5);

    const int row = rand() % 5;
    const int col = rand() % 5;

    Image img(0, "", cv::Mat());

    p_gridController->placeImage(row, col, &img);

    ASSERT_EQ(p_gridController->getTilesCount(), 1);
    
    const Tile *p_tile = p_gridController->getTileAt(row, col);
    ASSERT_EQ(p_tile->getRowMin(), row);
    ASSERT_EQ(p_tile->getColMin(), col);
    ASSERT_EQ(p_tile->getNbCells(), 1);
    ASSERT_EQ(p_tile->getImage(), &img);
    ASSERT_EQ(p_tile->getImage()->getId(), img.getId());

    ASSERT_FALSE(p_gridListener->getCreatedTiles().empty());
    ASSERT_EQ(p_gridListener->getCreatedTiles()[0]->getId(), p_tile->getId());

    ASSERT_FALSE(p_gridListener->getPlacedTiles().empty());
    ASSERT_EQ(p_gridListener->getPlacedTiles()[0].first->getId(), p_tile->getId());
    ASSERT_EQ(p_gridListener->getPlacedTiles()[0].second, &img);
    ASSERT_EQ(p_gridListener->getPlacedTiles()[0].second->getId(), img.getId());
}
