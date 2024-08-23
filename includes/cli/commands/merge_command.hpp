#ifndef MERGE_COMMAND_HPP
#define MERGE_COMMAND_HPP

#include "cli/commands/command.hpp"

/**
 * The command used by the cli to merge cells into a tile.
 */
class MergeCmd: public Command {
public:

    // Constructors
    MergeCmd(int rowMin, int colMin, int rowMax, int colMax);

    // Destructor

    // Getters

    // Setters

    // Instance's methods
    void execute(CLI *p_cli) override;

private:

    int m_rowMin;

    int m_colMin;

    int m_rowMax;

    int m_colMax;
};

#endif