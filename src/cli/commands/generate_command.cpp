#include "cli/commands/generate_command.hpp"
#include <iostream>

// Constructors

// Destructor

// Getters

// Setters

// Instance's methods
void GenerateCmd::execute(CLI *p_cli) {
    assert(p_cli != nullptr);
    assert(p_cli->getGridController() != nullptr);
    assert(p_cli->getWallpapersController() != nullptr);

    if(p_cli->getGridController()->generate()) {
        int id = p_cli->getWallpapersController()->getWallpapersCount() - 1;
        std::cout << "a new wallpaper has been generated and it has the id " << id << std::endl;
    } else {
        std::cout << "failed to generate a new wallpaper" << std::endl;
    }
}