#include "controllers/grid_controller.hpp"

// Constructors
GridController::GridController(): m_rows(3), m_cols(3), m_size(120) {
}

// Destructor
GridController::~GridController() {
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

// Setters
bool GridController::setRowsCount(int rows) {
    if(rows < 1) {
        return false;
    }

    m_rows = rows;
    return true;
}

bool GridController::setColsCount(int cols) {
    if(cols < 1) {
        return false;
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