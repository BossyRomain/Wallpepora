#include "gui/grid_editor_panel.hpp"
#include <wx/xrc/xh_all.h>
#include <wx/xrc/xmlres.h>
#include <wx/msgdlg.h>
#include <opencv2/opencv.hpp>

class DropTarget: public wxDropTarget {
public:

    // Constructors
    DropTarget(GridEditorPanel *p_parent);

    // Destructor

    // Getters

    // Setters

    // Instance's methods
    wxDragResult OnData(wxCoord x, wxCoord y, wxDragResult ref) override;

private:

    GridEditorPanel *m_parent;
};

// Constructors
DropTarget::DropTarget(GridEditorPanel *p_parent): m_parent(p_parent) {
    wxTextDataObject *p_dataObject = new wxTextDataObject();
    SetDataObject(p_dataObject);
}

// Destructor

// Getters

// Setters

// Instance's methods
wxDragResult DropTarget::OnData(wxCoord x, wxCoord y, wxDragResult ref) {
    if (GetData())
    {
        wxTextDataObject* textData = dynamic_cast<wxTextDataObject*>(GetDataObject());
        int id = 0;
        if(textData->GetText().ToInt(&id)) {
            m_parent->onImageDroped(x, y, id);
        }
    }
    return wxDragCopy;
}

/********************************************************************************
 * GridEditorPanel
 ********************************************************************************
 */

// Constructors
GridEditorPanel::GridEditorPanel(): m_gridController(nullptr), m_imagesController(nullptr) {
}

// Destructor
GridEditorPanel::~GridEditorPanel() {
}

// Getters
GridController* GridEditorPanel::getGridController() const {
    return m_gridController;
}

ImagesController* GridEditorPanel::getImagesController() const {
    return m_imagesController;
}

// Setters
void GridEditorPanel::setGridController(GridController *p_gridController) {
    m_gridController = p_gridController;
    m_paintArea->setGridController(p_gridController);
}

void GridEditorPanel::setImagesController(ImagesController *p_imagesController) {
    m_imagesController = p_imagesController;
}

// Instance's methods
void GridEditorPanel::Init() {
    m_scrolledWindow = XRCCTRL(*this, "scrolledWindow", wxScrolledWindow);
    m_scrolledWindow->SetScrollRate(10, 10);
    m_scrolledWindow->ShowScrollbars(wxSHOW_SB_DEFAULT, wxSHOW_SB_DEFAULT);

    m_paintArea = XRCCTRL(*this, "paint_area", GridPainter);
    m_paintArea->Bind(wxEVT_PAINT, &GridPainter::onPaint, m_paintArea);
    wxButton *mergeBtn = XRCCTRL(*this, "merge_btn", wxButton);
    wxButton *unmergeBtn = XRCCTRL(*this, "unmerge_btn", wxButton);
    wxButton *generateBtn = XRCCTRL(*this, "generate_btn", wxButton);
    wxSlider *p_zoomSlider = XRCCTRL(*this, "zoom_slider", wxSlider);
    wxButton *p_fillSoftBtn = XRCCTRL(*this, "fill_soft_btn", wxButton);
    wxButton *p_fillHardBtn = XRCCTRL(*this, "fill_hard_btn", wxButton);
    wxButton *p_clearBtn = XRCCTRL(*this, "clear_btn", wxButton);

    m_paintArea->Bind(wxEVT_LEFT_DOWN, &GridEditorPanel::onSelectionBegin, this);
    m_paintArea->Bind(wxEVT_LEFT_UP, &GridEditorPanel::onSelectionEnd, this);

    Bind(wxEVT_PAINT, &GridEditorPanel::sizedScrolledWindow, this);
    mergeBtn->Bind(wxEVT_BUTTON, &GridEditorPanel::merge, this);
    unmergeBtn->Bind(wxEVT_BUTTON, &GridEditorPanel::unmerge, this);
    generateBtn->Bind(wxEVT_BUTTON, &GridEditorPanel::generate, this);
    p_zoomSlider->Bind(wxEVT_SLIDER, &GridEditorPanel::onZoom, this);
    p_fillSoftBtn->Bind(wxEVT_BUTTON, &GridEditorPanel::onFillSoft, this);
    p_fillHardBtn->Bind(wxEVT_BUTTON, &GridEditorPanel::onFillHard, this);
    p_clearBtn->Bind(wxEVT_BUTTON, &GridEditorPanel::onClearGrid, this);

    SetDropTarget(new DropTarget(this));
}

void GridEditorPanel::sizedScrolledWindow(wxPaintEvent& event) {
    assert(m_gridController != nullptr);

    wxSize virtualSize(
        m_gridController->getColsCount() * m_paintArea->getCellsSize(), 
        m_gridController->getRowsCount() * m_paintArea->getCellsSize()
        );
    m_scrolledWindow->SetVirtualSize(virtualSize);
}

void GridEditorPanel::onSelectionBegin(wxMouseEvent& event) {
    m_startSelection = event.GetPosition();
    m_endSelection = wxPoint(-1, -1);

    m_paintArea->Bind(wxEVT_MOTION, &GridEditorPanel::onMouseMotion, this);
}

void GridEditorPanel::onSelectionEnd(wxMouseEvent& event) {
    m_endSelection = event.GetPosition();
    m_paintArea->Unbind(wxEVT_MOTION, &GridEditorPanel::onMouseMotion, this);
    
    wxRect selectionRect(m_startSelection, m_endSelection);
    if(selectionRect.GetWidth() > 10 || selectionRect.GetHeight() > 10) {
        m_paintArea->setSelecRect(selectionRect);
    } else {
        m_paintArea->setSelecRect(S_NO_SELECTION);

        int row = event.GetPosition().y / m_paintArea->getCellsSize();
        int col = event.GetPosition().x / m_paintArea->getCellsSize();

        m_paintArea->setSelectedTile(m_gridController->getTileAt(row, col));
    }
    m_paintArea->Refresh();
}

void GridEditorPanel::onImageDroped(wxCoord x, wxCoord y, int image_id) {
    wxPoint clientPos = m_scrolledWindow->CalcUnscrolledPosition(wxPoint(x, y));
    int row = clientPos.y / m_paintArea->getCellsSize();
    int col = clientPos.x / m_paintArea->getCellsSize();

    m_gridController->placeImage(row, col, m_imagesController->getImage(image_id));
    Refresh();
}

void GridEditorPanel::onMouseMotion(wxMouseEvent& event) {
    wxRect selectionRect(m_startSelection, event.GetPosition());
    if(selectionRect.GetWidth() > 10 || selectionRect.GetHeight() > 10) {
        m_paintArea->setSelecRect(selectionRect);
        Refresh();
    }
}

void GridEditorPanel::merge(wxCommandEvent& event) {
    int rowMin = (m_startSelection.y < m_endSelection.y ? m_startSelection.y : m_endSelection.y) / m_paintArea->getCellsSize();
    int colMin = (m_startSelection.x < m_endSelection.x ? m_startSelection.x : m_endSelection.x) / m_paintArea->getCellsSize();
    int rowMax = (m_startSelection.y > m_endSelection.y ? m_startSelection.y : m_endSelection.y) / m_paintArea->getCellsSize();
    int colMax = (m_startSelection.x > m_endSelection.x ? m_startSelection.x : m_endSelection.x) / m_paintArea->getCellsSize();

    m_startSelection = wxPoint(-1, -1);
    m_endSelection = wxPoint(-1, -1);

    m_paintArea->setSelecRect(S_NO_SELECTION);

    m_gridController->merge(rowMin, colMin, rowMax, colMax);
    Refresh();
}

void GridEditorPanel::unmerge(wxCommandEvent& event) {
    if(m_paintArea->getSelectedTile() != nullptr) {
        m_gridController->unmerge(m_paintArea->getSelectedTile()->getId());
        m_paintArea->setSelectedTile(nullptr);
        Refresh();
    }
}

void GridEditorPanel::generate(wxCommandEvent& event) {
    m_gridController->generate();
}

void GridEditorPanel::onZoom(wxCommandEvent& event) {
    wxSlider *p_zoomSlider = XRCCTRL(*this, "zoom_slider", wxSlider);
    float zoom;
    if(p_zoomSlider->GetValue() > 100) {
        zoom = (p_zoomSlider->GetValue() - 100 * 1.0f) / (p_zoomSlider->GetMax() - 100) + 1.0f;
    } else {
        zoom = ((p_zoomSlider->GetValue() - p_zoomSlider->GetMin() * 1.0f) / 100) + 0.5f;
    }

    if(zoom < m_paintArea->getZoom()) {
        m_scrolledWindow->Scroll(0, 0);
    }

    m_paintArea->setZoom(zoom);
    Refresh();
}

void GridEditorPanel::onFillSoft(wxCommandEvent& event) {
    m_gridController->fill(m_imagesController->getImages(), false);
    Refresh();
}

void GridEditorPanel::onFillHard(wxCommandEvent& event)  {
    m_gridController->fill(m_imagesController->getImages(), true);
    Refresh();
}

void GridEditorPanel::onClearGrid(wxCommandEvent& event) {
    wxMessageDialog dg(this, "This action will reset the grid and can't be canceled. Are you sure ?", "", wxYES_NO|wxNO_DEFAULT);
    if(dg.ShowModal() == wxID_YES) {
        m_gridController->clear();
        Refresh();
    }
}





wxIMPLEMENT_DYNAMIC_CLASS(GridEditorPanelXmlHandler, wxXmlResourceHandler);
 
GridEditorPanelXmlHandler::GridEditorPanelXmlHandler()
{
    AddWindowStyles();
}
 
wxObject *GridEditorPanelXmlHandler::DoCreateResource()
{
    XRC_MAKE_INSTANCE(control, GridEditorPanel)
 
    control->Create(m_parentAsWindow, GetID(), GetPosition(), GetSize(), GetStyle(), GetName());
    CreateChildren(control);
    control->Init();
 
    SetupWindow(control);
 
    return control;
}
 
bool GridEditorPanelXmlHandler::CanHandle(wxXmlNode *node)
{
    return IsOfClass(node, wxT("GridEditorPanel"));
}