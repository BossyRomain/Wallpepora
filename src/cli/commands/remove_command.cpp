#include "cli/commands/remove_command.hpp"

// Constructors
RemoveCmd::RemoveCmd(): m_removeAll(true), m_useTileId(false), m_tileId(0), m_row(0), m_col(0) {}

RemoveCmd::RemoveCmd(int tileId): m_removeAll(false), m_useTileId(true), m_tileId(tileId), m_row(0), m_col(0) {}

RemoveCmd::RemoveCmd(int row, int col): m_removeAll(false), m_useTileId(false), m_row(row), m_col(col), m_tileId(0) {}

// Destructor

// Getters

// Setters

// Instance's methods
void RemoveCmd::execute(CLI *p_cli) {
    assert(p_cli != nullptr);
    assert(p_cli->getGridController() != nullptr);
    
    if(m_removeAll) {
        for(Tile tile: p_cli->getGridController()->getTiles()) {
            p_cli->getGridController()->placeImage(tile.getId(), nullptr);
        }
    } else if(m_useTileId) {
        p_cli->getGridController()->placeImage(m_tileId, nullptr);
    } else {
        p_cli->getGridController()->placeImage(m_row, m_col, nullptr);
    }
}