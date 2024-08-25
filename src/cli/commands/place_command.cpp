#include "cli/commands/place_command.hpp"

// Constructors
PlaceCmd::PlaceCmd(int tileId, int imgId): m_useTileId(true), m_tileId(tileId), m_imgId(imgId), m_row(0), m_col(0) {
}

PlaceCmd::PlaceCmd(int row, int col, int imgId): m_useTileId(false), m_row(row), m_col(col), m_imgId(imgId), m_tileId(0) {
}

// Destructor

// Getters

// Setters

// Instance's methods
void PlaceCmd::execute(CLI *p_cli) {
    Image *p_image =p_cli->getImagesController()->getImage(m_imgId);

    if(m_useTileId) {
        p_cli->getGridController()->placeImage(m_tileId, p_image);
    } else {
        p_cli->getGridController()->placeImage(m_row, m_col, p_image);
    }
}