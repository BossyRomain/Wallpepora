#ifndef REMOVE_COMMAND_HPP
#define REMOVE_COMMAND_HPP

#include "cli/commands/command.hpp"

/**
 * The command used by the cli to remove an image from a cell or a tile (making it empty).
 */
class RemoveCmd: public Command {
public:

    // Constructors
    RemoveCmd(int tileId);

    RemoveCmd(int row, int col);

    // Destructor

    // Getters

    // Setters
    
    // Instance's methods
    void execute(CLI *p_cli) override;

private:

    bool m_useTileId;

    int m_tileId;

    int m_row;

    int m_col;

    int m_imgId;
};

#endif