#include "fixtures.hpp"
#include <filesystem>
namespace fs = std::filesystem;

/******************************************************
 ******************************************************
 ***                                                ***
 ***               TestImgsListener                 ***
 ***                                                ***
 ******************************************************
 ******************************************************/
// Constructors

// Destructor

// Getters
std::vector<Image*> TestImgsListener::getLoadedImgs() const {
    return m_loadedImgs;
}

std::vector<std::string> TestImgsListener::getLoadingFailedImgs() const {
    return m_loadingFailedImgs;
}

std::vector<Image> TestImgsListener::getDeletedImgs() const {
    return m_deletedImgs;
}

// Setters

// Instance's methods
void TestImgsListener::onImageLoaded(Image *p_image) {
    m_loadedImgs.push_back(p_image);
}

void TestImgsListener::onImageNotLoaded(const std::string& filePath) {
    m_loadingFailedImgs.push_back(filePath);
}

void TestImgsListener::onImageDeleted(Image image) {
    m_deletedImgs.push_back(image);
}

/******************************************************
 ******************************************************
 ***                                                ***
 ***                 ImagesFixture                  ***
 ***                                                ***
 ******************************************************
 ******************************************************/
// Constructors

// Destructor

// Getters
std::vector<std::string> ImagesFixture::getValidImgsPaths() const {
    return m_validImgsPaths;
}

std::vector<std::string> ImagesFixture::getInvalidImgsPaths() const {
    return m_invalidImgsPaths;
}

std::vector<std::string> ImagesFixture::getAllPaths() const {
    std::vector<std::string> paths = m_validImgsPaths;
    paths.insert(paths.end(), m_invalidImgsPaths.begin(), m_invalidImgsPaths.end());
    return paths;
}

// Setters

// Instance's methods
void ImagesFixture::SetUp() {
    p_imgsController = new ImagesController();
    p_imgsListener = new TestImgsListener();
    p_imgsController->addImagesListener(p_imgsListener);

    for(auto& file: fs::directory_iterator("./tests_res/images/valid/")) {
        m_validImgsPaths.push_back(file.path());
    }

    for(auto& file: fs::directory_iterator("./tests_res/images/invalid/")) {
        m_invalidImgsPaths.push_back(file.path());
        
        if(file.path().string().find("no_permissions") != std::string::npos) {
            fs::permissions(file.path(), fs::perms::none);
        }
    }
}

void ImagesFixture::TearDown() {
    p_imgsController->removeImagesListener(p_imgsListener);
    delete p_imgsController;
    delete p_imgsListener;

    for(std::string& file: m_invalidImgsPaths) {        
        if(file.find("no_permissions") != std::string::npos) {
            fs::permissions(file, fs::perms::all);
        }
    }
}

/******************************************************
 ******************************************************
 ***                                                ***
 ***               TestGridListener                 ***
 ***                                                ***
 ******************************************************
 ******************************************************/
// Constructors
TestGridListener::TestGridListener(): m_rows(-1), m_cols(-1), m_size(-1) {}

// Destructor

// Getters
int TestGridListener::getRowsCount() const {
    return m_rows;
}

int TestGridListener::getColsCount() const {
    return m_cols;
}

int TestGridListener::getCellsSize() const {
    return m_size;
}

std::vector<const Tile*> TestGridListener::getCreatedTiles() const {
    return m_created;
}

std::vector<const Tile*> TestGridListener::getResizedTiles() const {
    return m_resized;
}

std::vector<Tile> TestGridListener::getDeletedTiles() const {
    return m_deleted;
}

std::vector<std::pair<const Tile*, const Image*>> TestGridListener::getPlacedTiles() const {
    return m_placed;
}

// Setters

// Instance's methods
void TestGridListener::onRowsUpdated(int rows) {
    m_rows = rows;
}

void TestGridListener::onColsUpdated(int cols) {
    m_cols = cols;
}

void TestGridListener::onCellsSizeUpdated(int size) {
    m_size = size;
}

void TestGridListener::onTileCreated(const Tile *p_tile) {
    m_created.push_back(p_tile);
}

void TestGridListener::onTileResized(const Tile *p_tile) {
    m_resized.push_back(p_tile);
}

void TestGridListener::onTileDeleted(Tile tile) {
    m_deleted.push_back(tile);
}

void TestGridListener::onImagePlaced(const Tile *p_tile, const Image *p_image) {
    m_placed.push_back(std::make_pair(p_tile, p_image));
}

/******************************************************
 ******************************************************
 ***                                                ***
 ***                 GridFixture                    ***
 ***                                                ***
 ******************************************************
 ******************************************************/
void GridFixture::SetUp() {
    p_gridController = new GridController();
    p_gridListener = new TestGridListener();

    p_gridController->addGridListener(p_gridListener);
}

void GridFixture::TearDown() {
    p_gridController->removeGridListener(p_gridListener);

    delete p_gridController;
    delete p_gridListener;
}