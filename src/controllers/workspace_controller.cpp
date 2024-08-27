#include "controllers/workspace_controller.hpp"
#include <fstream>
#include <iostream>

int readInt(std::ifstream& stream) {
    int value;
    stream.read((char*) &value, sizeof(int));
    return value;
}

std::string readStr(std::ifstream& stream) {
    std::string str;
    size_t size;
    stream.read((char*) &size, sizeof(size));
    str.resize(size);
    stream.read((char*) &str[0], size);
    return str; 
}

void writeInt(std::ofstream& stream, int value) {
    stream.write((char*) &value, sizeof(int));
}

void writeStr(std::ofstream& stream, const std::string& str) {
    size_t size = str.length();
    stream.write((char*) &size, sizeof(size));
    stream.write((char*) &str[0], size);
}

// Constructors
WorkspaceController::WorkspaceController(): m_imagesController(nullptr), m_gridController(nullptr) {
}

// Destructor
WorkspaceController::~WorkspaceController() {
}

// Getters
ImagesController* WorkspaceController::getImagesController() const {
    return m_imagesController;
}

GridController* WorkspaceController::getGridController() const {
    return m_gridController;
}

// Setters
void WorkspaceController::setImagesController(ImagesController *p_imagesController) {
    m_imagesController = p_imagesController;
}

void WorkspaceController::setGridController(GridController *p_gridController) {
    m_gridController = p_gridController;
}

// Instance's methods
void WorkspaceController::load(const std::string& filePath) {
    std::ifstream workspace(filePath, std::ios::binary);

    m_imagesController->loadFromWorkspace(workspace);
    m_gridController->loadFromWorkspace(workspace, m_imagesController);

    workspace.close();
}

void WorkspaceController::save(const std::string& filePath) {
    std::ofstream workspace(filePath, std::ios::binary);

    m_imagesController->saveInWorkspace(workspace);
    m_gridController->saveInWorkspace(workspace);

    workspace.close();
}