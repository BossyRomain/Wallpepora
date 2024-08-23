#include "gui/grid_params_panel.hpp"
#include <wx/xrc/xh_all.h>
#include <wx/xrc/xmlres.h>

// Constructors
GridParamsPanel::GridParamsPanel(wxWindow *p_parent): m_gridController(nullptr) {
    wxXmlResource::Get()->LoadPanel(this, p_parent, "grid_params_panel");

    m_rowsSpinner = XRCCTRL(*this, "rows_spinner", wxSpinCtrl);
    m_rowsSpinner->Bind(wxEVT_SPINCTRL, &GridParamsPanel::onRowsUpdate, this);

    m_colsSpinner = XRCCTRL(*this, "cols_spinner", wxSpinCtrl);
    m_colsSpinner->Bind(wxEVT_SPINCTRL, &GridParamsPanel::onColsUpdate, this);

    m_cellsSizeSpinner = XRCCTRL(*this, "size_spinner", wxSpinCtrl);
    m_cellsSizeSpinner->Bind(wxEVT_SPINCTRL, &GridParamsPanel::onCellsSizeUpdate, this);
}

// Destructor
GridParamsPanel::~GridParamsPanel() {
}

// Getters
GridController* GridParamsPanel::getGridController() const {
    return m_gridController;
}

GridEditorPanel* GridParamsPanel::getGridEditorPanel() const {
    return m_gridEditorPanel;
}

// Setters
void GridParamsPanel::setGridController(GridController *p_gridController) {
    m_gridController = p_gridController;

    if(m_gridController != nullptr) {
        m_rowsSpinner->SetValue(m_gridController->getRowsCount());
        m_colsSpinner->SetValue(m_gridController->getColsCount());
        m_cellsSizeSpinner->SetValue(m_gridController->getCellsSize());
    }
}

void GridParamsPanel::setGridEditorPanel(GridEditorPanel *p_gridEditorPanel) {
    m_gridEditorPanel = p_gridEditorPanel;
}

// Instance's methods
void GridParamsPanel::onRowsUpdate(wxSpinEvent& event) {
    assert(m_gridController != nullptr);
    assert(m_gridEditorPanel != nullptr);

    if(!m_gridController->setRowsCount(event.GetValue())) {
        m_rowsSpinner->SetValue(m_gridController->getRowsCount());
    } else {
        m_gridEditorPanel->Refresh();
        m_gridEditorPanel->Update();
    }
}

void GridParamsPanel::onColsUpdate(wxSpinEvent& event) {
    assert(m_gridController != nullptr);
    assert(m_gridEditorPanel != nullptr);

    if(!m_gridController->setColsCount(event.GetValue())) {
        m_colsSpinner->SetValue(m_gridController->getColsCount());
    } else {
        m_gridEditorPanel->Refresh();
        m_gridEditorPanel->Update();
    }

}

void GridParamsPanel::onCellsSizeUpdate(wxSpinEvent& event) {
    assert(m_gridController != nullptr);
    assert(m_gridEditorPanel != nullptr);

    if(!m_gridController->setCellsSize(event.GetValue())) {
        m_cellsSizeSpinner->SetValue(m_gridController->getCellsSize());
    } else {
        m_gridEditorPanel->Refresh();
        m_gridEditorPanel->Update();
    }
}