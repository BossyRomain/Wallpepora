#ifndef COMMAND_HPP
#define COMMAND_HPP

#include "cli/cli.hpp"

class CLI;

/**
 * The interface implemented by every commands used by the CLI.
 */
class Command {
public:

    /**
     * Executes the command.
     * 
     * @param p_cli a pointer to the CLI's object that calls this method.
     */
    virtual void execute(CLI *p_cli) =0;
};

#endif