#include "cli/commands/reset_command.hpp"
#include "cli/cli_utils.hpp"

// Constructors

// Destructor

// Getters

// Setters

// Instance's methods
void ResetCmd::execute(CLI *p_cli) {
    assert(p_cli != nullptr);
    assert(p_cli->getGridController() != nullptr);

    if(confirmAction("This action will reset the grid (remove all the tiles) and can't be canceled. Are you sure ?")) {
        p_cli->getGridController()->clear();
    }
}