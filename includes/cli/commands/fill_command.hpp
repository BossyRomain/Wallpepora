#ifndef FILL_COMMAND_HPP
#define FILL_COMMAND_HPP

#include "cli/commands/command.hpp"

/**
 * This command fill the cells and the tiles of the grid with images.
 * 
 * There is two types of fill :
 * - soft - images are placed only in empty cells and empty tiles.
 * - hard - images are placed in every cell and every tile, even if they already have an image.
 */
class FillCmd: public Command {
public:

    // Constructors
    /**
     * Constructs a fill command with a soft fill by default.
     * 
     * @param hardFill - true if the command will do a hard fill, else the command will do a soft fill.
     */
    FillCmd(bool hardFill = false);

    // Destructor

    // Getters

    // Setters

    // Instance's methods
    void execute(CLI *p_cli) override;

private:

    bool m_hardFill;
};

#endif