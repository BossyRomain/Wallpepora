#include "cli/commands/remove_command.hpp"

// Constructors
RemoveCmd::RemoveCmd(int tileId): m_useTileId(true), m_tileId(tileId), m_row(0), m_col(0) {
}

RemoveCmd::RemoveCmd(int row, int col): m_useTileId(false), m_row(row), m_col(col), m_tileId(0) {
}

// Destructor

// Getters

// Setters

// Instance's methods
void RemoveCmd::execute(CLI *p_cli) {
    if(m_useTileId) {
        p_cli->getGridController()->placeImage(m_tileId, nullptr);
    } else {
        p_cli->getGridController()->placeImage(m_row, m_col, nullptr);
    }
}