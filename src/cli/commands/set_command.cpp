#include "cli/commands/set_command.hpp"
#include <iostream>
#include <regex>

// Constructors
SetCmd::SetCmd(std::vector<std::string> args): m_args(args) {
}

// Destructor

// Getters

// Setters

// Instance's method
void SetCmd::execute(CLI *p_cli) {
    try {
        if(m_args.empty()) {
            throw std::exception();
        }

        int rows = -1;
        int cols = -1;
        int size = -1;
        for(int i = 0; i < m_args.size(); i++) {
            if(m_args[i] == "-r") {
                rows = std::stoi(m_args[i+1]);
                i++;
            } else if(m_args[i] == "-c") {
                cols = std::stoi(m_args[i+1]);
                i++;
            } else if(m_args[i] == "-s") {
                size = std::stoi(m_args[i+1]);
                i++;
            } else if(std::regex_match(m_args[i], std::regex("--rows=[0-9]+"))) {
                rows = std::stoi(m_args[i].substr(m_args[i].find_first_of('=') + 1));
            } else if(std::regex_match(m_args[i], std::regex("--cols=[0-9]+"))) {
                cols = std::stoi(m_args[i].substr(m_args[i].find_first_of('=') + 1));
            } else if(std::regex_match(m_args[i], std::regex("--size=[0-9]+"))) {
                size = std::stoi(m_args[i].substr(m_args[i].find_first_of('=') + 1));
            } else {
                throw std::exception();
            }
        }

        if(rows >= 0) {
            updateRows(p_cli->getGridController(), rows);
        }
        if(cols >= 0) {
            updateCols(p_cli->getGridController(), cols);
        }
        if(size >= 0) {
            updateSize(p_cli->getGridController(), size);
        }

    } catch(...) {
        std::cout << "invalid command" << std::endl;
    }
}

void SetCmd::updateRows(GridController *p_gridController, int rows) const {
    if(p_gridController->setRowsCount(rows)) {
        std::cout << "grid's number of rows updated" << std::endl;
    } else {
        std::cout << "error while updating grid's number of rows" << std::endl;
    }
}

void SetCmd::updateCols(GridController *p_gridController, int cols) const {
    if(p_gridController->setColsCount(cols)) {
        std::cout << "grid's number of columns updated" << std::endl;
    } else {
        std::cout << "error while updating grid's number of columns" << std::endl;
    }
}

void SetCmd::updateSize(GridController *p_gridController, int size) const {
    if(p_gridController->setCellsSize(size)) {
        std::cout << "grid's cells' size updated" << std::endl;
    } else {
        std::cout << "error while updating grid's cells' size" << std::endl;
    }
}