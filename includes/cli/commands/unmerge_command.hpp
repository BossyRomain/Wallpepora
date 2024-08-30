#ifndef UNMERGE_COMMAND_HPP
#define UNMERGE_COMMAND_HPP

#include "cli/commands/command.hpp"

/**
 * This command unmerge a tile on the grid using its id.
 */
class UnmergeCmd: public Command {
public:

    // Constructors
    /**
     * Constructs a unmerge command with the specified id.
     * 
     * @param id - a tile id.
     */
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