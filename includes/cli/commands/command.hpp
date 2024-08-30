#ifndef COMMAND_HPP
#define COMMAND_HPP

#include "cli/cli.hpp"

class CLI;

/**
 * The interface implemented by every command used by the CLI.
 * 
 * Each command need to implement the pure virtual method execute.
 */
class Command {
public:

    /**
     * The method used by the CLI to executes the command.
     * 
     * @param p_cli a pointer of the CLI's object that calls this method.
     */
    virtual void execute(CLI *p_cli) =0;
};

#endif