#ifndef GRID_EDITOR_WINDOW_HPP
#define GRID_EDITOR_WINDOW_HPP

#include <wx/wx.h>
#include "controllers/grid_controller.hpp"
#include "gui/paint_area.hpp"

/**
 * The panel inside the GUI which permits the user :
 * - to merge cells into tiles
 * - to unmerge tiles into cells
 */
class GridEditorPanel: public wxPanel {
public:

    // Constructors
    GridEditorPanel(wxWindow *p_parent);

    // Destructor
    ~GridEditorPanel();

    // Getters
    GridController* getGridController() const;

    // Setters
    void setGridController(GridController *p_gridController);

    // Instance's methods
    /**
     * Invoked when the user press the left button of his mouse.
     */
    void onSelectionBegin(wxMouseEvent& event);

    /**
     * Invoked when the user release the left button of his mouse.
     */
    void onSelectionEnd(wxMouseEvent& event);

private:
    // Instance's methods
    /**
     * Invoked when the grid's dimensions are updated.
     * Update the virtual size of the wxScrolledWindow containing the PaintArea's object attribute of this object.
     */
    void sizedScrolledWindow(wxPaintEvent& event);

    /**
     * Invoked when the user moves his mouse cursor on the grid.
     */
    void onMouseMotion(wxMouseEvent& event);

    /**
     * Invoked when the user clicks on the button to merge cells.
     */
    void merge(wxCommandEvent& event);

    /**
     * Invoked when the user clicks on the button to unmerge a tile.
     */
    void unmerge(wxCommandEvent& event);

    // Attributes
    GridController *m_gridController;

    wxScrolledWindow *p_scrolledWindow;

    PaintArea *m_paintArea;

    wxPoint m_startSelection;

    wxPoint m_endSelection;
};

#endif