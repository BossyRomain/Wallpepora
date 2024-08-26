#include "cli/commands/fill_command.hpp"

// Constructors
FillCmd::FillCmd(bool hardFill): m_hardFill(hardFill) {
}

// Destructor

// Getters

// Setters

// Instance's methods
void FillCmd::execute(CLI *p_cli) {
    p_cli->getGridController()->fill(p_cli->getImagesController()->getImages(), m_hardFill);
}