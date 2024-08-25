#include "cli/commands/generate_command.hpp"
#include <iostream>

// Constructors

// Destructor

// Getters

// Setters

// Instance's methods
void GenerateCmd::execute(CLI *p_cli) {
    if(p_cli->getGridController()->generate()) {
        std::cout << "a new wallpaper has been generated" << std::endl;
    } else {
        std::cout << "failed to generate a new wallpaper" << std::endl;
    }
}