#include "controllers/grid_controller.hpp"
#include <exception>

// Helpers functions
bool compareTiles(Tile *p_tile1, Tile *p_tile2) {
    return p_tile1->getId() < p_tile2->getId();
}

// Constructors
GridController::GridController(): m_rows(3), m_cols(3), m_size(120), m_tiles() {
}

// Destructor
GridController::~GridController() {
    for(Tile *p_tile: m_tiles) {
        delete p_tile;
    }
    m_tiles.clear();
}

// Getters
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

// Setters
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

        i = 0;
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