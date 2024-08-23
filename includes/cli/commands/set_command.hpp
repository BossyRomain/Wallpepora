#ifndef SET_COMMAND_HPP
#define SET_COMMAND_HPP

#include "cli/commands/command.hpp"
#include <vector>

class SetCmd: public Command {
public:

    // Constructors
    SetCmd(std::vector<std::string> args);

    // Destructor

    // Getters

    // Setters

    // Instance's method
    void execute(CLI *p_cli) override;

private:

    // Instance's methods
    void updateRows(GridController *p_gridController, int rows) const;

    void updateCols(GridController *p_gridController, int cols) const;

    void updateSize(GridController *p_gridController, int size) const;

    // Attributes
    std::vector<std::string> m_args;
};

#endif