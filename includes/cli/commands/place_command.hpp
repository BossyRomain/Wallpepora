#ifndef PLACE_COMMAND_HPP
#define PLACE_COMMAND_HPP

#include "cli/commands/command.hpp"

/**
 * This command places an image with one of the following methods :
 * - in a cell using its coordinates.
 * - in a tile using its id.
 * - in a tile using the coordinates of one the cell contained in the targeted tile.
 */
class PlaceCmd: public Command {
public:

    // Constructors
    /**
     * Constructs a place command that will place an image in a tile using its id.
     */
    PlaceCmd(int tileId, int imgId);

    /**
     * Constructs a place command that will place an image in a cell using its coordinates or 
     * in a tile using the coordinates of one of the contained cells in the targeted tile.
     */
    PlaceCmd(int row, int col, int imgId);

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