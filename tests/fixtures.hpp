#ifndef FIXTURES_HPP
#define FIXTURES_HPP

#include <gtest/gtest.h>
#include <vector>
#include <utility>
#include "controllers/images_controller.hpp"
#include "controllers/grid_controller.hpp"
#include "model/images.hpp"

/******************************************************
 ******************************************************
 ***                                                ***
 ***               TestImgsListener                 ***
 ***                                                ***
 ******************************************************
 ******************************************************/
class TestImgsListener: public ImagesListener {
public:

    // Constructors

    // Destructor

    // Getters
    std::vector<Image*> getLoadedImgs() const;

    std::vector<std::string> getLoadingFailedImgs() const;

    std::vector<Image> getDeletedImgs() const;

    // Setters

    // Instance's methods
    void onImageLoaded(Image *p_image) override;

    void onImageNotLoaded(const std::string& filePath) override;

    void onImageDeleted(Image image) override;

private:

    std::vector<Image*> m_loadedImgs;

    std::vector<std::string> m_loadingFailedImgs;

    std::vector<Image> m_deletedImgs;
};

/******************************************************
 ******************************************************
 ***                                                ***
 ***                 ImagesFixture                  ***
 ***                                                ***
 ******************************************************
 ******************************************************/
class ImagesFixture: public testing::Test {
public:

    // Constructors

    // Destructor

    // Getters
    std::vector<std::string> getValidImgsPaths() const;

    std::vector<std::string> getInvalidImgsPaths() const;

    std::vector<std::string> getAllPaths() const;

    // Setters

    // Instance's methods

    // Attributes
    ImagesController *p_imgsController;
    
    TestImgsListener *p_imgsListener;

protected:

    // Instance's methods
    void SetUp() override;

    void TearDown() override;

private:

    std::vector<std::string> m_validImgsPaths;

    std::vector<std::string> m_invalidImgsPaths;
};

/******************************************************
 ******************************************************
 ***                                                ***
 ***               TestGridListener                 ***
 ***                                                ***
 ******************************************************
 ******************************************************/
class TestGridListener: public GridListener {
public:

    // Constructors
    TestGridListener();

    // Destructor

    // Getters
    int getRowsCount() const;

    int getColsCount() const;

    int getCellsSize() const;

    std::vector<const Tile*> getCreatedTiles() const;

    std::vector<const Tile*> getResizedTiles() const;

    std::vector<Tile> getDeletedTiles() const;

    std::vector<std::pair<const Tile*, const Image*>> getPlacedTiles() const;

    // Setters

    // Instance's methods
    void onRowsUpdated(int rows) override;
    
    void onColsUpdated(int cols) override;
    
    void onCellsSizeUpdated(int size) override;
    
    void onTileCreated(const Tile *p_tile) override;
    
    void onTileResized(const Tile *p_tile) override;
    
    void onTileDeleted(Tile tile) override;
    
    void onImagePlaced(const Tile *p_tile, const Image *p_image) override;

private:

    int m_rows;

    int m_cols;

    int m_size;
    
    std::vector<const Tile*> m_created;

    std::vector<const Tile*> m_resized;

    std::vector<Tile> m_deleted;

    std::vector<std::pair<const Tile*, const Image*>> m_placed;
};

/******************************************************
 ******************************************************
 ***                                                ***
 ***                 GridFixture                    ***
 ***                                                ***
 ******************************************************
 ******************************************************/
class GridFixture: public testing::Test {
public:

    // Constructors

    // Destructor

    // Getters

    // Setters

    // Instance's methods

    // Attributes
    GridController *p_gridController;

    TestGridListener *p_gridListener;

protected:

    // Instance's methods
    void SetUp() override;

    void TearDown() override;

private:
};

#endif