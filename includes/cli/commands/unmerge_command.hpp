#ifndef UNMERGE_COMMAND_HPP
#define UNMERGE_COMMAND_HPP

#include "cli/commands/command.hpp"

/**
 * The command used by the cli to unmerge a tile into cells using its id.
 */
class UnmergeCmd: public Command {
public:

    // Constructors
    UnmergeCmd(int id);

    // Destructor

    // Getters

    // Setters

    // Instance's methods
    void execute(CLI *p_cli) override;

private:

    int m_id;
};

#endif