#include "cli/commands/merge_command.hpp"
#include <iostream>

// Constructors
MergeCmd::MergeCmd(int rowMin, int colMin, int rowMax, int colMax):
m_rowMin(rowMin), m_colMin(colMin), m_rowMax(rowMax), m_colMax(colMax) {
}

// Destructor

// Getters

// Setters

// Instance's methods
void MergeCmd::execute(CLI *p_cli) {
    int id = p_cli->getGridController()->merge(m_rowMin, m_colMin, m_rowMax, m_colMax);
    if(id >= 0) {
        std::cout << "new tile created with the id " << id << std::endl;
    } else {
        std::cout << "failed to create a new tile" << std::endl;
    }
}