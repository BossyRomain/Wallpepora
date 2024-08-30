#include "cli/commands/unmerge_command.hpp"
#include <iostream>

// Constructors
UnmergeCmd::UnmergeCmd(int id): m_id(id) {}

// Destructor

// Getters

// Setters

// Instance's methods
void UnmergeCmd::execute(CLI *p_cli) {
    assert(p_cli != nullptr);
    assert(p_cli->getGridController() != nullptr);

    try {
        p_cli->getGridController()->unmerge(m_id);
        std::cout << "the tile with the id " << m_id << " has been deleted" << std::endl;
    } catch(std::out_of_range& e) {
        std::cout << "there is no tile on the grid with the id " << m_id << std::endl;
    }
}