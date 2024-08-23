#ifndef PAINT_AREA_HPP
#define PAINT_AREA_HPP

#include <wx/wx.h>
#include "controllers/grid_controller.hpp"

const static wxRect S_NO_SELECTION(wxPoint(-1, -1), wxSize(0, 0));

/**
 * Draw the current state of the grid inside the GUI.
 * Also draw other elements like the rectangle of selection when the user selects cells to merge.
 */
class PaintArea: public wxPanel {
public:

    // Constructors
    PaintArea(wxWindow *p_parent);

    // Destructor

    // Getters
    GridController* getGridController() const;

    wxRect getSelectRect() const;

    const Tile* getSelectedTile() const;

    // Setters
    void setGridController(GridController *p_gridController);

    void setSelecRect(wxRect selection);

    void setSelectedTile(const Tile *p_tile);

    // Instance's methods
    /**
     * Invoked when the GUI is refreshed.
     */
    void onPaint(wxPaintEvent& event);

private:

    // Instance's methods
    /**
     * Draws a tile.
     */
    void drawTile(wxPaintDC& dc, const Tile& tile);

    /**
     * Draws a cell.
     */
    void drawCell(wxPaintDC& dc, int row, int col);

    // Attributes
    GridController *m_gridController;

    wxRect m_selectRect;

    const Tile *m_selectedTile;
};

#endif