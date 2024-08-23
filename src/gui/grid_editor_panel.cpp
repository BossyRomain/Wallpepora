#include "gui/grid_editor_panel.hpp"
#include <wx/xrc/xh_all.h>
#include <wx/xrc/xmlres.h>
#include <opencv2/opencv.hpp>

// Constructors
PaintArea::PaintArea(wxWindow *p_parent): wxPanel(p_parent, wxID_ANY), m_gridController(nullptr) {
    Bind(wxEVT_PAINT, &PaintArea::onPaint, this);
}

// Destructor

// Getters
GridController* PaintArea::getGridController() const {
    return m_gridController;
}

// Setters
void PaintArea::setGridController(GridController *p_gridController) {
    m_gridController = p_gridController;

    if(m_gridController != nullptr) {
        SetVirtualSize(wxSize(
            m_gridController->getColsCount() * m_gridController->getCellsSize(),
            m_gridController->getRowsCount() * m_gridController->getCellsSize()
        ));
    }
}

// Instance's methods
void PaintArea::onPaint(wxPaintEvent& event) {
    assert(m_gridController != nullptr);
    SetClientSize(
        m_gridController->getColsCount() * m_gridController->getCellsSize(),
        m_gridController->getRowsCount() * m_gridController->getCellsSize()
    );

    wxSize v = GetClientSize();

    wxPaintDC dc(this);

    cv::Mat img(
        cv::Size(m_gridController->getColsCount() * m_gridController->getCellsSize(), m_gridController->getRowsCount() * m_gridController->getCellsSize()), 
        CV_8UC3, 
        cv::Scalar(255, 255, 0)
    );
    wxImage image(img.cols, img.rows, img.data, true);
    wxBitmap bmp(image);

    dc.DrawBitmap(bmp, wxPoint(200, 200));
}


// Constructors
GridEditorPanel::GridEditorPanel(wxWindow *p_parent): m_gridController(nullptr) {
    wxXmlResource::Get()->LoadPanel(this, p_parent, "grid_editor_panel");

    p_scrolledWindow = new wxScrolledWindow(this);
    p_scrolledWindow->SetScrollRate(10, 10);
    p_scrolledWindow->ShowScrollbars(wxSHOW_SB_DEFAULT, wxSHOW_SB_DEFAULT);

    p_paintArea = new PaintArea(p_scrolledWindow);

    wxSizer *p_sizer = GetSizer();
    p_sizer->Add(p_scrolledWindow, 1, wxALL|wxEXPAND, 10);

    Bind(wxEVT_PAINT, &GridEditorPanel::sizedScrolledWindow, this);
}

// Destructor
GridEditorPanel::~GridEditorPanel() {
}

// Getters
GridController* GridEditorPanel::getGridController() const {
    return m_gridController;
}

// Setters
void GridEditorPanel::setGridController(GridController *p_gridController) {
    m_gridController = p_gridController;
    p_paintArea->setGridController(p_gridController);
}

// Instance's methods
void GridEditorPanel::sizedScrolledWindow(wxPaintEvent& event) {
    assert(m_gridController != nullptr);

    wxSize size(
        m_gridController->getColsCount() * m_gridController->getCellsSize(),
        m_gridController->getRowsCount() * m_gridController->getCellsSize()
    );
    p_scrolledWindow->SetVirtualSize(
        size
    );
}