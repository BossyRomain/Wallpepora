#include "gui/grid_params_panel.hpp"
#include <wx/xrc/xh_all.h>
#include <wx/xrc/xmlres.h>

/******************************************************
 ******************************************************
 ***                                                ***
 ***                 GridParamsPanel                ***
 ***                                                ***
 ******************************************************
 ******************************************************/
// Constructors
GridParamsPanel::GridParamsPanel(): m_gridController(nullptr) {}

// Destructor
GridParamsPanel::~GridParamsPanel() {
    m_gridController->removeGridListener(this);
}

// Getters
GridController* GridParamsPanel::getGridController() const {
    return m_gridController;
}

// Setters
void GridParamsPanel::setGridController(GridController *p_gridController) {
    if(m_gridController != nullptr) {
        m_gridController->removeGridListener(this);
    }

    m_gridController = p_gridController;
    m_gridController->addGridListener(this);

    m_rowsSpinner->SetValue(m_gridController->getRowsCount());
    m_colsSpinner->SetValue(m_gridController->getColsCount());
    m_cellsSizeSpinner->SetValue(m_gridController->getCellsSize());
}

// Instance's methods
void GridParamsPanel::onRowsUpdated(int rows) {
    m_rowsSpinner->SetValue(rows);
}

void GridParamsPanel::onColsUpdated(int cols) {
    m_colsSpinner->SetValue(cols);    
}

void GridParamsPanel::onCellsSizeUpdated(int size) {
    m_cellsSizeSpinner->SetValue(size);
}

void GridParamsPanel::Init() {
    m_rowsSpinner = XRCCTRL(*this, "rows_spinner", wxSpinCtrl);
    m_rowsSpinner->Bind(wxEVT_SPINCTRL, &GridParamsPanel::onUpdateRows, this);

    m_colsSpinner = XRCCTRL(*this, "cols_spinner", wxSpinCtrl);
    m_colsSpinner->Bind(wxEVT_SPINCTRL, &GridParamsPanel::onUpdateCols, this);

    m_cellsSizeSpinner = XRCCTRL(*this, "size_spinner", wxSpinCtrl);
    m_cellsSizeSpinner->Bind(wxEVT_SPINCTRL, &GridParamsPanel::onUpdateCellsSize, this);
}

void GridParamsPanel::onUpdateRows(wxSpinEvent& event) {
    assert(m_gridController != nullptr);
    m_gridController->setRowsCount(event.GetValue());
}

void GridParamsPanel::onUpdateCols(wxSpinEvent& event) {
    assert(m_gridController != nullptr);
    m_gridController->setColsCount(event.GetValue());
}

void GridParamsPanel::onUpdateCellsSize(wxSpinEvent& event) {
    assert(m_gridController != nullptr);
    m_gridController->setCellsSize(event.GetValue());
}


/******************************************************
 ******************************************************
 ***                                                ***
 ***          GridParamsPanelXmlHandler             ***
 ***                                                ***
 ******************************************************
 ******************************************************/
wxIMPLEMENT_DYNAMIC_CLASS(GridParamsPanelXmlHandler, wxXmlResourceHandler);
 
GridParamsPanelXmlHandler::GridParamsPanelXmlHandler()
{
    AddWindowStyles();
}
 
wxObject *GridParamsPanelXmlHandler::DoCreateResource()
{
    XRC_MAKE_INSTANCE(control, GridParamsPanel)
    
    control->Create(m_parentAsWindow, GetID(), GetPosition(), GetSize(), GetStyle(), GetName());
    CreateChildren(control);
    control->Init();
 
    SetupWindow(control);
 
    return control;
}
 
bool GridParamsPanelXmlHandler::CanHandle(wxXmlNode *node)
{
    return IsOfClass(node, wxT("GridParamsPanel"));
}