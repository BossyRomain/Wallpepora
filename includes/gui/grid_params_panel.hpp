#ifndef GRID_PARAMS_PANEL_HPP
#define GRID_PARAMS_PANEL_HPP

#include <wx/wx.h>
#include <wx/spinctrl.h>
#include "controllers/grid_controller.hpp"
#include "gui/grid_editor_panel.hpp"

/**
 * The panel inside the GUI which permits the user :
 * - to change the number of rows of the grid
 * - to change the number of columns of the grid
 * - to change the size of cells of the grid
 */
class GridParamsPanel: public wxPanel {
public:

    // Constructors
    GridParamsPanel(wxWindow *p_parent);

    // Destructor
    ~GridParamsPanel();

    // Getters
    GridController* getGridController() const;

    GridEditorPanel* getGridEditorPanel() const;

    // Setters
    void setGridController(GridController *p_gridController);

    void setGridEditorPanel(GridEditorPanel *p_gridEditorPanel);

    // Instance's methods

private:

    // Instance's methods
    void onRowsUpdate(wxSpinEvent& event);

    void onColsUpdate(wxSpinEvent& event);

    void onCellsSizeUpdate(wxSpinEvent& event);

    // Attributes
    GridController *m_gridController;

    GridEditorPanel *m_gridEditorPanel;

    wxSpinCtrl *m_rowsSpinner;
    
    wxSpinCtrl *m_colsSpinner;

    wxSpinCtrl *m_cellsSizeSpinner;
};

#endif