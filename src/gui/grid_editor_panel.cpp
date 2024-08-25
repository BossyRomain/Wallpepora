#include "gui/grid_editor_panel.hpp"
#include <wx/xrc/xh_all.h>
#include <wx/xrc/xmlres.h>
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
GridEditorPanel::GridEditorPanel(wxWindow *p_parent): m_gridController(nullptr), m_imagesController(nullptr) {
    wxXmlResource::Get()->LoadPanel(this, p_parent, "grid_editor_panel");

    p_scrolledWindow = new wxScrolledWindow(this);
    p_scrolledWindow->SetScrollRate(10, 10);
    p_scrolledWindow->ShowScrollbars(wxSHOW_SB_DEFAULT, wxSHOW_SB_DEFAULT);

    m_paintArea = new PaintArea(p_scrolledWindow);
    wxButton *mergeBtn = XRCCTRL(*this, "merge_btn", wxButton);
    wxButton *unmergeBtn = XRCCTRL(*this, "unmerge_btn", wxButton);
    wxButton *generateBtn = XRCCTRL(*this, "generate_btn", wxButton);

    wxGridBagSizer *p_sizer = (wxGridBagSizer*) GetSizer();

    p_sizer->Add(p_scrolledWindow, wxGBPosition(1, 0), wxDefaultSpan, wxALL|wxEXPAND);

    m_paintArea->Bind(wxEVT_LEFT_DOWN, &GridEditorPanel::onSelectionBegin, this);
    m_paintArea->Bind(wxEVT_LEFT_UP, &GridEditorPanel::onSelectionEnd, this);

    Bind(wxEVT_PAINT, &GridEditorPanel::sizedScrolledWindow, this);
    mergeBtn->Bind(wxEVT_BUTTON, &GridEditorPanel::merge, this);
    unmergeBtn->Bind(wxEVT_BUTTON, &GridEditorPanel::unmerge, this);
    generateBtn->Bind(wxEVT_BUTTON, &GridEditorPanel::generate, this);

    mergeBtn->SetBitmap(wxBitmap("./res/icons/merge.png"));
    unmergeBtn->SetBitmap(wxBitmap("./res/icons/unmerge.png"));

    SetDropTarget(new DropTarget(this));
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
void GridEditorPanel::sizedScrolledWindow(wxPaintEvent& event) {
    assert(m_gridController != nullptr);

    wxSize size(
        m_gridController->getColsCount() * m_gridController->getCellsSize(),
        m_gridController->getRowsCount() * m_gridController->getCellsSize()
    );
    p_scrolledWindow->SetVirtualSize(size);
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

        int row = event.GetPosition().y / m_gridController->getCellsSize();
        int col = event.GetPosition().x / m_gridController->getCellsSize();

        m_paintArea->setSelectedTile(m_gridController->getTileAt(row, col));
    }
    m_paintArea->Refresh();
}

void GridEditorPanel::onImageDroped(wxCoord x, wxCoord y, int image_id) {
    int row = (y - y % m_gridController->getCellsSize()) / m_gridController->getCellsSize();
    int col = (x - x % m_gridController->getCellsSize()) / m_gridController->getCellsSize();

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
    int rowMin = (m_startSelection.y < m_endSelection.y ? m_startSelection.y : m_endSelection.y) / m_gridController->getCellsSize();
    int colMin = (m_startSelection.x < m_endSelection.x ? m_startSelection.x : m_endSelection.x) / m_gridController->getCellsSize();
    int rowMax = (m_startSelection.y > m_endSelection.y ? m_startSelection.y : m_endSelection.y) / m_gridController->getCellsSize();
    int colMax = (m_startSelection.x > m_endSelection.x ? m_startSelection.x : m_endSelection.x) / m_gridController->getCellsSize();

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