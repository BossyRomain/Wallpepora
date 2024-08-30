#ifndef GRID_PARAMS_PANEL_HPP
#define GRID_PARAMS_PANEL_HPP

#include <wx/wx.h>
#include <wx/spinctrl.h>
#include <wx/xrc/xh_all.h>
#include <wx/xrc/xmlres.h>
#include "controllers/grid_controller.hpp"
#include "gui/grid_editor_panel.hpp"

/**
 * The panel inside the GUI which permits the user :
 * - to change the number of rows of the grid
 * - to change the number of columns of the grid
 * - to change the size of cells of the grid
 */
class GridParamsPanel: public wxPanel, public GridListener {
public:

    // Constructors
    GridParamsPanel();
    
    // Destructor
    ~GridParamsPanel();

    // Getters
    GridController* getGridController() const;

    // Setters
    void setGridController(GridController *p_gridController);

    // Instance's methods
    void onRowsUpdated(int rows) override;

    void onColsUpdated(int cols) override;

    void onCellsSizeUpdated(int size) override;

    void Init();

private:

    // Instance's methods
    void onUpdateRows(wxSpinEvent& event);

    void onUpdateCols(wxSpinEvent& event);

    void onUpdateCellsSize(wxSpinEvent& event);

    // Attributes
    GridController *m_gridController;

    wxSpinCtrl *m_rowsSpinner;
    
    wxSpinCtrl *m_colsSpinner;

    wxSpinCtrl *m_cellsSizeSpinner;
};

class GridParamsPanelXmlHandler : public wxXmlResourceHandler
{
public:
    // Constructor.
    GridParamsPanelXmlHandler();
 
    // Creates the control and returns a pointer to it.
    virtual wxObject *DoCreateResource();
 
    // Returns true if we know how to create a control for the given node.
    virtual bool CanHandle(wxXmlNode *node);
 
    // Register with wxWidgets' dynamic class subsystem.
    wxDECLARE_DYNAMIC_CLASS(GridParamsPanelXmlHandler);
};


#endif