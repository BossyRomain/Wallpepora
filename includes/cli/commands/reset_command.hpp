#ifndef CLEAR_COMMAND_HPP
#define CLEAR_COMMAND_HPP

#include "cli/commands/command.hpp"

/**
 * This command resets the grid.
 */
class ResetCmd: public Command {
public:

    // Constructors

    // Destructor

    // Getters

    // Setters

    // Instance's methods
    void execute(CLI *p_cli) override;
    
private:
};

#endif