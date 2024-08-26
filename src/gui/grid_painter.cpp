#include "gui/grid_painter.hpp"
#include <opencv2/opencv.hpp>

// Static variables
static const wxBrush SELECTION_BRUSH(wxColour(254, 254, 250, 150));

// Constructors
GridPainter::GridPainter(): m_gridController(nullptr), m_selectRect(S_NO_SELECTION), m_selectedTile(nullptr), m_zoom(1.0f) {
}

// Destructor

// Getters
GridController* GridPainter::getGridController() const {
    return m_gridController;
}

wxRect GridPainter::getSelectRect() const {
    return m_selectRect;
}

const Tile* GridPainter::getSelectedTile() const {
    return m_selectedTile;
}

float GridPainter::getZoom() const {
    return m_zoom;
}

int GridPainter::getCellsSize() const {
    return (int) (m_zoom * m_gridController->getCellsSize());
}

// Setters
void GridPainter::setGridController(GridController *p_gridController) {
    m_gridController = p_gridController;
}

void GridPainter::setSelecRect(wxRect selection) {
    m_selectRect = selection;
}

void GridPainter::setSelectedTile(const Tile *p_tile) {
    m_selectedTile = p_tile;
}

void GridPainter::setZoom(float zoom) {
    m_zoom = zoom;
}

// Instance's methods
void GridPainter::onPaint(wxPaintEvent& event) {
    if(m_gridController == nullptr) {
        return;
    }

    SetClientSize(m_gridController->getColsCount() * getCellsSize(), m_gridController->getRowsCount() * getCellsSize());

    wxScrolledWindow *p_parent = dynamic_cast<wxScrolledWindow*>(GetParent());

    int rowMin = p_parent->GetViewStart().y * 10 / getCellsSize();
    int colMin = p_parent->GetViewStart().x * 10 / getCellsSize();
    int rowMax = (p_parent->GetViewStart().y * 10 + p_parent->GetClientSize().GetHeight()) / getCellsSize();
    int colMax = (p_parent->GetViewStart().x * 10 + p_parent->GetClientSize().GetWidth()) / getCellsSize();

    wxPaintDC dc(this);

    int i = 0;
    Tile visibleTile(0, rowMin, colMin, rowMax, colMax);
    std::vector<Tile> tiles = m_gridController->getTiles();
    for(Tile tile: tiles) {
        if(tile.intersect(visibleTile)) {
            drawTile(dc, tile);
        }
    }
    

    for(int r = 0; r < m_gridController->getRowsCount(); r++) {
        for(int c = 0; c < m_gridController->getColsCount(); c++) {
            if(visibleTile.cellIn(r, c)) {
                int j = 0;
                while(j < tiles.size() && !tiles[j].cellIn(r, c)) {
                    j++;
                }

                if(j == tiles.size()) {
                    drawCell(dc, r, c);
                }
            }
        }
    }

    if(m_selectRect.GetTopLeft() != wxPoint(-1, -1) && m_selectRect.GetBottomRight() != wxPoint(-1, -1)) {
        dc.SetBrush(SELECTION_BRUSH);

        dc.DrawRectangle(m_selectRect);
    }
}

void GridPainter::drawTile(wxPaintDC& dc, const Tile& tile) {
    wxPoint topLeft(tile.getColMin() * getCellsSize(), tile.getRowMin() * getCellsSize());
    wxSize rectSize(tile.getWitdh() * getCellsSize(), tile.getHeight() * getCellsSize());

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
        cv::Size(tile.getWitdh() * getCellsSize(), tile.getHeight() * getCellsSize()));

        cv::Mat rgb;
        cv::cvtColor(resized, rgb, cv::COLOR_BGR2RGB);

        wxImage image(rgb.cols, rgb.rows, rgb.data, true);
        wxBitmap bmp(image);
        dc.DrawBitmap(bmp, topLeft);
    }
}

void GridPainter::drawCell(wxPaintDC& dc, int row, int col) {
    wxPoint topLeft(col * getCellsSize(), row * getCellsSize());
    wxSize rectSize(getCellsSize(), getCellsSize());

    wxRect rect(topLeft, rectSize);
    wxBrush brush = dc.GetBrush();
    if(rect.Intersects(m_selectRect)) {
        dc.SetBrush(wxBrush(wxColour(200, 200, 200)));
    }

    dc.DrawRectangle(rect);
    dc.SetBrush(brush);
}




wxIMPLEMENT_DYNAMIC_CLASS(GridPainterXmlHandler, wxXmlResourceHandler);
 
GridPainterXmlHandler::GridPainterXmlHandler()
{
    AddWindowStyles();
}
 
wxObject *GridPainterXmlHandler::DoCreateResource()
{
    XRC_MAKE_INSTANCE(control, GridPainter)
    
    control->Create(m_parentAsWindow, GetID(), GetPosition(), GetSize(), GetStyle(), GetName());
    CreateChildren(control);
 
    SetupWindow(control);
 
    return control;
}
 
bool GridPainterXmlHandler::CanHandle(wxXmlNode *node)
{
    return IsOfClass(node, wxT("GridPainter"));
}