#include "cli/commands/fill_command.hpp"

// Constructors
FillCmd::FillCmd(bool hardFill): m_hardFill(hardFill) {}

// Destructor

// Getters

// Setters

// Instance's methods
void FillCmd::execute(CLI *p_cli) {
    assert(p_cli != nullptr);
    assert(p_cli->getImagesController() != nullptr);
    assert(p_cli->getGridController() != nullptr);

    p_cli->getGridController()->fill(p_cli->getImagesController()->getImages(), m_hardFill);
}