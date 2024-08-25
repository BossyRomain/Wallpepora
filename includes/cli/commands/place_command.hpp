#ifndef PLACE_COMMAND_HPP
#define PLACE_COMMAND_HPP

#include "cli/commands/command.hpp"

class PlaceCmd: public Command {
public:

    // Constructors
    PlaceCmd(int tileId, int imgId);

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