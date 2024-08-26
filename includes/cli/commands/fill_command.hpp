#ifndef FILL_COMMAND_HPP
#define FILL_COMMAND_HPP

#include "cli/commands/command.hpp"

class FillCmd: public Command {
public:

    // Constructors
    FillCmd(bool hardFill = false);

    // Destructor

    // Getters

    // Setters

    // Instance's methods
    void execute(CLI *p_cli) override;

private:

    bool m_hardFill;
};

#endif