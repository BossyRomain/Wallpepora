#include "controllers/grid_controller.hpp"
#include <exception>
#include <random>

// Helpers functions
bool compareTiles(Tile *p_tile1, Tile *p_tile2) {
    return p_tile1->getId() < p_tile2->getId();
}

// Constructors
GridController::GridController(): m_rows(7), m_cols(7), m_size(120), m_tiles() {
}

// Destructor
GridController::~GridController() {
    clear();
}

// Getters
WallpapersController* GridController::getWallpapersController() const {
    return m_wallpapersController;
}

int GridController::getRowsCount() const {
    return m_rows;
}

int GridController::getColsCount() const {
    return m_cols;
}

int GridController::getCellsSize() const {
    return m_size;
}

int GridController::getTilesCount() const {
    return m_tiles.size();
}

const Tile* GridController::getTile(int id) const {
    int i = 0;
    while(i < m_tiles.size() && m_tiles[i]->getId() != id) {
        i++;
    }

    return i < m_tiles.size() ? m_tiles[i] : nullptr; 
}

const Tile* GridController::getTileAt(int row, int col) const {
    int i = 0;
    while(i < m_tiles.size() && !m_tiles[i]->cellIn(row, col)) {
        i++;
    }

    return i < m_tiles.size() ? m_tiles[i] : nullptr;
}

std::vector<Tile> GridController::getTiles() const {
    std::vector<Tile> tiles;
    for(Tile *p_tile: m_tiles) {
        tiles.push_back(Tile(*p_tile));
    }
    return tiles;
}

bool GridController::isComplete() const {
    int sum = 0;
    bool allHaveImages = true;
    for(Tile *p_tile: m_tiles) {
        if(p_tile->getImage() != nullptr) {
            sum += p_tile->getNbCells();
        } else {
            allHaveImages = false;
        }
    }
    return allHaveImages && sum == m_rows * m_cols;
}

// Setters
void GridController::setWallpapersController(WallpapersController *p_wallpapersController) {
    m_wallpapersController = p_wallpapersController;
}

bool GridController::setRowsCount(int rows) {
    if(rows < 1) {
        return false;
    }

    for(auto it = m_tiles.begin(); it < m_tiles.end();) {
        Tile *p_tile = (*it);
        if(p_tile->getRowMin() >= rows) {
            delete p_tile;
            it = m_tiles.erase(it);
        } else if(p_tile->getRowMax() >= rows) {
            p_tile->setRowMax(rows - 1);
            it++;
        } else {
            it++;
        }
    }

    m_rows = rows;
    return true;
}

bool GridController::setColsCount(int cols) {
    if(cols < 1) {
        return false;
    }

    for(auto it = m_tiles.begin(); it < m_tiles.end();) {
        Tile *p_tile = (*it);
        if(p_tile->getColMin() >= cols) {
            delete p_tile;
            it = m_tiles.erase(it);
        } else if(p_tile->getColMax() >= cols) {
            p_tile->setColMax(cols - 1);
            it++;
        } else {
            it++;
        }
    }

    m_cols = cols;
    return true;
}

bool GridController::setCellsSize(int size) {
    if(size < 20) {
        return false;
    }

    m_size = size;
    return true;
}

// Instance's methods
int GridController::merge(int rowMin, int colMin, int rowMax, int colMax) {
    Tile tile(0, rowMin, colMin, rowMax, colMax);

    int i = 0;
    while(i < m_tiles.size() && (m_tiles[i]->getNbCells() == 1 || !m_tiles[i]->intersect(tile))) {
        i++;
    }

    if(i == m_tiles.size()) {
        // Possible to create the new tile
        return addNewTile(rowMin, colMin, rowMax, colMax);
    }

    return -1;
}

void GridController::unmerge(int id) {
    int i = 0;
    while(i < m_tiles.size() && m_tiles[i]->getId() != id) {
        i++;
    }

    if(i < m_tiles.size()) {
        delete m_tiles[i];
        m_tiles.erase(m_tiles.begin() + i);
    } else {
        throw std::out_of_range("");
    }
}

void GridController::placeImage(int row, int col, Image *p_image)  {
    int i =  0;
    while(i < m_tiles.size() && !m_tiles[i]->cellIn(row, col)) {
        i++;
    }

    if(i < m_tiles.size()) {
        // A tile contains this cell
        m_tiles[i]->setImage(p_image);
    } else {
        // No tile contains this cell
        int id = addNewTile(row, col, row, col);
        
        i = 0;
        while(i < m_tiles.size() && m_tiles[i]->getId() != id) {
            i++;
        }

        m_tiles[i]->setImage(p_image);
    }
}

void GridController::placeImage(int id, Image *p_image) {
    int i = 0;
    while(i < m_tiles.size() && m_tiles[i]->getId() != id) {
        i++;
    }

    if(i < m_tiles.size()) {
        m_tiles[i]->setImage(p_image);
    }
}

int GridController::addNewTile(int rowMin, int colMin, int rowMax, int colMax) {
    Tile tile(0, rowMin, colMin, rowMax, colMax);
    if(!m_tiles.empty()) {
        for(auto it = m_tiles.begin(); it < m_tiles.end();) {
            if((*it)->getNbCells() == 1 && (*it)->intersect(tile)) {
                delete (*it);
                it = m_tiles.erase(it);
            } else {
                it++;
            }
        }
    }

    int i = 0;
    int id = 0;
    while(i < m_tiles.size() && m_tiles[i]->getId() == id) {
        id = m_tiles[i]->getId() + 1;
        i++;
    }

    Tile *p_tile = new Tile(id, rowMin, colMin, rowMax, colMax);
    m_tiles.push_back(p_tile);

    std::sort(m_tiles.begin(), m_tiles.end(), compareTiles);
    return id;
}

bool GridController::generate() {
    if(!isComplete()) {
        return false;
    }

    cv::Mat wallpaper(cv::Size(m_cols * m_size, m_rows * m_size), CV_8UC3);

    for(Tile *p_tile: m_tiles) {
        int x = p_tile->getColMin() * m_size;
        int y = p_tile->getRowMin() * m_size;
        int width = (p_tile->getColMax() - p_tile->getColMin() + 1) * m_size;
        int height = (p_tile->getRowMax() - p_tile->getRowMin() + 1) * m_size;

        cv::Mat data = p_tile->getImage()->getData();
        cv::Mat resized;
        cv::resize(data, resized, cv::Size(width, height));

        for(int i = 0; i < height; i++) {
            for(int j = 0; j < width; j++) {
                cv::Vec3b pixel = resized.at<cv::Vec3b>(i, j);
                wallpaper.at<cv::Vec3b>(y + i, x + j) = pixel;
            } 
        }
    }

    m_wallpapersController->add(wallpaper);

    return true;
}

void GridController::fill(std::vector<Image*> images, bool hard) {
    if(images.empty()) {
        return;
    }

    std::shuffle(images.begin(), images.end(), std::default_random_engine(time(NULL)));
    int i = 0;
    for(Tile *p_tile: m_tiles) {
        if(p_tile->getImage() == nullptr || hard) {
            p_tile->setImage(images[i]);
            i++;
        }

        if(i == images.size()) {
            std::shuffle(images.begin(), images.end(), std::default_random_engine(time(NULL)));
            i = 0;
        }
    }

    for(int r = 0; r < m_rows; r++) {
        for(int c = 0; c < m_cols; c++) {
            if(getTileAt(r, c) == nullptr) {
                placeImage(r, c, images[i]);
                i++;
            }

            if(i == images.size()) {
                std::shuffle(images.begin(), images.end(), std::default_random_engine(time(NULL)));
                i = 0;
            }
        }
    }
}

void GridController::clear() {
    for(Tile *p_tile: m_tiles) {
        delete p_tile;
    }
    m_tiles.clear();
}