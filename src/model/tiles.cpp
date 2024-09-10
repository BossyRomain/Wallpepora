#include "model/tiles.hpp"

// Constructors
Tile::Tile(int id, int rowMin, int colMin, int rowMax, int colMax):
m_id(id), m_rowMin(rowMin), m_colMin(colMin), m_rowMax(rowMax), m_colMax(colMax), m_image(nullptr) {
}

Tile::Tile(const Tile& tile):
m_id(tile.m_id), m_rowMin(tile.m_rowMin), m_colMin(tile.m_colMin), m_rowMax(tile.m_rowMax), m_colMax(tile.m_colMax), m_image(tile.m_image) {
}

// Destructor
Tile::~Tile() {
}

// Getters
int Tile::getId() const {
    return m_id;
}

int Tile::getRowMin() const {
    return m_rowMin;
}

int Tile::getColMin() const {
    return m_colMin;
}

int Tile::getRowMax() const {
    return m_rowMax;
}

int Tile::getColMax() const {
    return m_colMax;
}

int Tile::getWidth() const {
    return m_colMax - m_colMin + 1;
}

int Tile::getHeight() const {
    return m_rowMax - m_rowMin + 1;
}

int Tile::getNbCells() const {
    return getWidth() * getHeight();
}

Image* Tile::getImage() const {
    return m_image;
}

// Setters
void Tile::setRowMax(int rowMax) {
    m_rowMax = rowMax;
}

void Tile::setColMax(int colMax) {
    m_colMax = colMax;
}

void Tile::setImage(Image *p_image) {
    m_image = p_image;
}

// Instance's methods
bool Tile::intersect(const Tile& other) const {
    if(m_colMin > other.m_colMax || other.m_colMin > m_colMax) {
        return false;
    } 

    if(m_rowMin > other.m_rowMax || other.m_rowMin > m_rowMax) {
        return false;
    }

    return true;
}

bool Tile::cellIn(int row, int col) const {
    return m_rowMin <= row && row <= m_rowMax && m_colMin <= col && col <= m_colMax;
}