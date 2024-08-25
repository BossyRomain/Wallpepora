
#ifndef GENERATE_COMMAND_HPP
#define GENERATE_COMMAND_HPP

#include "cli/commands/command.hpp"

/**
 * The command used by the cli to generates a new wallpaper if possible.
 */
class GenerateCmd: public Command {
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