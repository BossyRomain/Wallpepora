#ifndef REMOVE_COMMAND_HPP
#define REMOVE_COMMAND_HPP

#include "cli/commands/command.hpp"

/**
 * This command removes an image with one of the following methods :
 * - from a cell using its coordinates.
 * - from a tile using its id.
 * - from a tile using the coordinates of one the cell contained in the targeted tile.
 */
class RemoveCmd: public Command {
public:

    // Constructors
    /**
     * Constructs a remove command that will remove the image in a tile using its id.
     */
    RemoveCmd(int tileId);

    /**
     * Constructs a remove command that will remove an image in a cell using its coordinates or 
     * in a tile using the coordinates of one of the contained cells in the targeted tile.
     */
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