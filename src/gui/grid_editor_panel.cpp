#include "gui/grid_editor_panel.hpp"
#include <wx/xrc/xh_all.h>
#include <wx/xrc/xmlres.h>
#include <wx/msgdlg.h>
#include <opencv2/opencv.hpp>
#include <cmath>

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
            m_parent->onImageDropped(x, y, id);
        }
    }
    return wxDragCopy;
}

/********************************************************************************
 * GridEditorPanel
 ********************************************************************************
 */

// Constructors
GridEditorPanel::GridEditorPanel(): m_gridController(nullptr), m_imagesController(nullptr), m_oldRows(0), m_oldCols(0) {
}

// Destructor
GridEditorPanel::~GridEditorPanel() {
    m_gridController->removeGridListener(this);
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
    if(m_gridController != nullptr) {
        m_gridController->removeGridListener(this);
    }
    m_gridController = p_gridController;
    m_gridController->addGridListener(this);
    m_oldRows = m_gridController->getRowsCount();
    m_oldCols = m_gridController->getColsCount();
    m_paintArea->setGridController(p_gridController);
}

void GridEditorPanel::setImagesController(ImagesController *p_imagesController) {
    m_imagesController = p_imagesController;
}

// Instance's methods
void GridEditorPanel::onRowsUpdated(int rows) {
    if(rows < m_oldRows) {
        wxPoint p = m_scrolledWindow->GetViewStart();
        p.y -= (m_oldRows - rows) * 10;
        m_scrolledWindow->Scroll(p);
    }
    m_oldRows = rows;
    Refresh();
}

void GridEditorPanel::onColsUpdated(int cols) {
    if(cols < m_oldCols) {
        wxPoint p = m_scrolledWindow->GetViewStart();
        p.x -= (m_oldCols - cols) * 10;
        m_scrolledWindow->Scroll(p);
    }
    m_oldCols = cols;
    Refresh();
}

void GridEditorPanel::onCellsSizeUpdated(int size) {
    Refresh();
}

void GridEditorPanel::onTileCreated(const Tile *p_tile) {
    Refresh();
}

void GridEditorPanel::onTileDeleted(Tile tile) {
    Refresh();
}

void GridEditorPanel::onImagePlaced(const Tile *p_tile, const Image *p_image) {
    Refresh();
}

void GridEditorPanel::Init() {
    m_scrolledWindow = XRCCTRL(*this, "scrolledWindow", wxScrolledWindow);
    m_scrolledWindow->SetScrollRate(10, 10);
    m_scrolledWindow->ShowScrollbars(wxSHOW_SB_DEFAULT, wxSHOW_SB_DEFAULT);

    m_paintArea = XRCCTRL(*this, "paint_area", GridPainter);
    m_paintArea->Bind(wxEVT_PAINT, &GridPainter::onPaint, m_paintArea);
    m_paintArea->Bind(wxEVT_LEFT_DOWN, &GridEditorPanel::onSelectionBegin, this);
    m_paintArea->Bind(wxEVT_LEFT_UP, &GridEditorPanel::onSelectionEnd, this);

    wxToolBar *p_toolbar = XRCCTRL(*this, "toolbar", wxToolBar);
    p_toolbar->Bind(wxEVT_TOOL, &GridEditorPanel::merge, this, XRCID("merge_btn"));
    p_toolbar->Bind(wxEVT_TOOL, &GridEditorPanel::unmerge, this, XRCID("unmerge_btn"));
    p_toolbar->Bind(wxEVT_TOOL, &GridEditorPanel::onZoomIn, this, XRCID("zoom_in_btn"));
    p_toolbar->Bind(wxEVT_TOOL, &GridEditorPanel::onZoomOut, this, XRCID("zoom_out_btn"));
    p_toolbar->Bind(wxEVT_TOOL, &GridEditorPanel::onFillSoft, this, XRCID("fill_soft_btn"));
    p_toolbar->Bind(wxEVT_TOOL, &GridEditorPanel::onFillHard, this, XRCID("fill_hard_btn"));
    p_toolbar->Bind(wxEVT_TOOL, &GridEditorPanel::onRemoveImages, this, XRCID("remove_images_btn"));
    p_toolbar->Bind(wxEVT_TOOL, &GridEditorPanel::onResetGrid, this, XRCID("reset_grid_btn"));

    wxButton *p_generateBtn = XRCCTRL(*this, "generate_btn", wxButton);
    p_generateBtn->Bind(wxEVT_BUTTON, &GridEditorPanel::generate, this);

    Bind(wxEVT_PAINT, &GridEditorPanel::sizedScrolledWindow, this);

    SetDropTarget(new DropTarget(this));
}

void GridEditorPanel::sizedScrolledWindow(wxPaintEvent& event) {
    m_scrolledWindow->SetVirtualSize(m_paintArea->GetClientSize());
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
}

void GridEditorPanel::onImageDropped(wxCoord x, wxCoord y, int image_id) {
    wxPoint clientPos = m_scrolledWindow->CalcUnscrolledPosition(wxPoint(x, y));
    int row = clientPos.y / m_paintArea->getCellsSize();
    int col = clientPos.x / m_paintArea->getCellsSize();

    m_gridController->placeImage(row, col, m_imagesController->getImage(image_id));
}

void GridEditorPanel::onMouseMotion(wxMouseEvent& event) {
    wxRect selectionRect(m_startSelection, event.GetPosition());
    if(selectionRect.GetWidth() > 10 || selectionRect.GetHeight() > 10) {
        m_paintArea->setSelecRect(selectionRect);
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
}

void GridEditorPanel::unmerge(wxCommandEvent& event) {
    if(m_paintArea->getSelectedTile() != nullptr) {
        m_gridController->unmerge(m_paintArea->getSelectedTile()->getId());
        m_paintArea->setSelectedTile(nullptr);
    }
}

void GridEditorPanel::generate(wxCommandEvent& event) {
    m_gridController->generate();
}

void GridEditorPanel::onZoomIn(wxCommandEvent& event) {
    float zoom = m_paintArea->getZoom();
    zoom += 0.05f;

    if(zoom > 2.0f) {
        zoom = 2.0f;
    }
    
    m_paintArea->setZoom(zoom);
}

void GridEditorPanel::onZoomOut(wxCommandEvent& event) {
    float zoom = m_paintArea->getZoom();
    zoom -= 0.05f;

    if(zoom < 0.5f) {
        zoom = 0.5f;
    }   

    m_paintArea->setZoom(zoom);

    int scrollX, scrollY;
    m_scrolledWindow->GetScrollPixelsPerUnit(&scrollX, &scrollY);
    int x = m_scrolledWindow->GetScrollPos(wxHORIZONTAL) - static_cast<int>(zoom * scrollX);
    int y = m_scrolledWindow->GetScrollPos(wxVERTICAL) - static_cast<int>(zoom * scrollY);
    m_scrolledWindow->Scroll(x, y);
}

void GridEditorPanel::onFillSoft(wxCommandEvent& event) {
    m_gridController->fill(m_imagesController->getImages(), false);
}

void GridEditorPanel::onFillHard(wxCommandEvent& event)  {
    m_gridController->fill(m_imagesController->getImages(), true);
}

void GridEditorPanel::onRemoveImages(wxCommandEvent& event) {
    wxMessageDialog dg(this, "This action will remove all the images on the grid and can't be canceled. Are you sure ?", "", wxYES_NO|wxNO_DEFAULT);
    if(dg.ShowModal() == wxID_YES) {
        for(Tile tile: m_gridController->getTiles()) {
            m_gridController->placeImage(tile.getId(), nullptr);
        }
    }
}

void GridEditorPanel::onResetGrid(wxCommandEvent& event) {
    wxMessageDialog dg(this, "This action will reset the grid and can't be canceled. Are you sure ?", "", wxYES_NO|wxNO_DEFAULT);
    if(dg.ShowModal() == wxID_YES) {
        m_gridController->clear();
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