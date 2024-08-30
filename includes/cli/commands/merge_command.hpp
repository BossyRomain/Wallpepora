#ifndef MERGE_COMMAND_HPP
#define MERGE_COMMAND_HPP

#include "cli/commands/command.hpp"

/**
 * This command merges cells into a tile.
 * 
 * If the merging success, the id of the new tile is shown, else an error message is shown. 
 */
class MergeCmd: public Command {
public:

    // Constructors
    /**
     * Constructs a merge command with the coordinates of the cells to merge.
     * 
     * @param rowMin - the first row index of the cells.
     * @param colMin - the first column index of the cells.
     * @param rowMax - the last row index of the cells.
     * @param colMax - the last column index of the cells.
     */
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