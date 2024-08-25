#include "cli/commands/export_command.hpp"
#include <iostream>

// Constructors
ExportCmd::ExportCmd(int id, const std::string& filePath): m_id(id), m_filePath(filePath) {
}

// Destructor

// Getters

// Setters

// Instance's methods
void ExportCmd::execute(CLI *p_cli) {
    if(p_cli->getWallpapersController()->exportWallpaper(m_filePath, m_id)) {
        std::cout << "the wallpaper with the id " << m_id << " has been successfully export in the file " << m_filePath << std::endl;
    } else {
        std::cout << "exportation failed" << std::endl;
    }
}