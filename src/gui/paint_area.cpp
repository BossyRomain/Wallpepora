#include "gui/paint_area.hpp"
#include <opencv2/opencv.hpp>

// Static variables
static const wxBrush SELECTION_BRUSH(wxColour(254, 254, 250, 150));

// Constructors
PaintArea::PaintArea(): m_gridController(nullptr), m_selectRect(S_NO_SELECTION), m_selectedTile(nullptr), m_zoom(1.0f) {
}

// Destructor

// Getters
GridController* PaintArea::getGridController() const {
    return m_gridController;
}

wxRect PaintArea::getSelectRect() const {
    return m_selectRect;
}

const Tile* PaintArea::getSelectedTile() const {
    return m_selectedTile;
}

float PaintArea::getZoom() const {
    return m_zoom;
}

// Setters
void PaintArea::setGridController(GridController *p_gridController) {
    m_gridController = p_gridController;
}

void PaintArea::setSelecRect(wxRect selection) {
    m_selectRect = selection;
}

void PaintArea::setSelectedTile(const Tile *p_tile) {
    m_selectedTile = p_tile;
}

void PaintArea::setZoom(float zoom) {
    m_zoom = zoom;
}

// Instance's methods
void PaintArea::onPaint(wxPaintEvent& event) {
    if(m_gridController == nullptr) {
        return;
    }

    int cellsSize = (int) (m_zoom * m_gridController->getCellsSize());
    SetClientSize(m_gridController->getColsCount() * cellsSize, m_gridController->getRowsCount() * cellsSize);

    cv::Scalar colors[5] = {cv::Scalar(255, 255, 0), cv::Scalar(255, 0, 0), cv::Scalar(0, 255, 0), cv::Scalar(0, 0, 255), cv::Scalar(0, 255, 255)};
    wxPaintDC dc(this);

    std::vector<Tile> tiles = m_gridController->getTiles();
    int i = 0;
    for(Tile tile: tiles) {
        drawTile(dc, cellsSize, tile);
    }

    for(int r = 0; r < m_gridController->getRowsCount(); r++) {
        for(int c = 0; c < m_gridController->getColsCount(); c++) {
            int j = 0;
            while(j < tiles.size() && !tiles[j].cellIn(r, c)) {
                j++;
            }

            if(j == tiles.size()) {
                drawCell(dc, cellsSize, r, c);
            }
        }
    }

    if(m_selectRect.GetTopLeft() != wxPoint(-1, -1) && m_selectRect.GetBottomRight() != wxPoint(-1, -1)) {
        dc.SetBrush(SELECTION_BRUSH);

        dc.DrawRectangle(m_selectRect);
    }
}

void PaintArea::drawTile(wxPaintDC& dc, int cellsSize, const Tile& tile) {
    wxPoint topLeft(tile.getColMin() * cellsSize, tile.getRowMin() * cellsSize);
    wxSize rectSize(tile.getWitdh() * cellsSize, tile.getHeight() * cellsSize);

    if(tile.getImage() == nullptr) {
        wxRect rect(topLeft, rectSize);
        wxBrush brush = dc.GetBrush();
        if(rect.Intersects(m_selectRect) || (m_selectedTile != nullptr && m_selectedTile->getId() == tile.getId())) {
            dc.SetBrush(wxBrush(wxColour(200, 200, 200)));
        }

        dc.DrawRectangle(rect);
        dc.SetBrush(brush);
    } else {
        cv::Mat resized;
        cv::resize(tile.getImage()->getData(), resized, 
        cv::Size(tile.getWitdh() * cellsSize, tile.getHeight() * cellsSize));

        cv::Mat rgb;
        cv::cvtColor(resized, rgb, cv::COLOR_BGR2RGB);

        wxImage image(rgb.cols, rgb.rows, rgb.data, true);
        wxBitmap bmp(image);
        dc.DrawBitmap(bmp, topLeft);
    }
}

void PaintArea::drawCell(wxPaintDC& dc, int cellsSize, int row, int col) {
    wxPoint topLeft(col * cellsSize, row * cellsSize);
    wxSize rectSize(cellsSize, cellsSize);

    wxRect rect(topLeft, rectSize);
    wxBrush brush = dc.GetBrush();
    if(rect.Intersects(m_selectRect)) {
        dc.SetBrush(wxBrush(wxColour(200, 200, 200)));
    }

    dc.DrawRectangle(rect);
    dc.SetBrush(brush);
}




wxIMPLEMENT_DYNAMIC_CLASS(PaintAreaXmlHandler, wxXmlResourceHandler);
 
PaintAreaXmlHandler::PaintAreaXmlHandler()
{
    AddWindowStyles();
}
 
wxObject *PaintAreaXmlHandler::DoCreateResource()
{
    XRC_MAKE_INSTANCE(control, PaintArea)
    
    control->Create(m_parentAsWindow, GetID(), GetPosition(), GetSize(), GetStyle(), GetName());
    CreateChildren(control);
 
    SetupWindow(control);
 
    return control;
}
 
bool PaintAreaXmlHandler::CanHandle(wxXmlNode *node)
{
    return IsOfClass(node, wxT("PaintArea"));
}