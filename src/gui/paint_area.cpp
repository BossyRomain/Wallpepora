#include "gui/paint_area.hpp"
#include <opencv2/opencv.hpp>

// Static variables
static const wxBrush SELECTION_BRUSH(wxColour(125, 125, 125, 100));

// Constructors
PaintArea::PaintArea(wxWindow *p_parent): wxPanel(p_parent, wxID_ANY), m_gridController(nullptr), m_selectRect(S_NO_SELECTION), m_selectedTile(nullptr) {
    Bind(wxEVT_PAINT, &PaintArea::onPaint, this);
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

void PaintArea::setSelecRect(wxRect selection) {
    m_selectRect = selection;
}

void PaintArea::setSelectedTile(const Tile *p_tile) {
    m_selectedTile = p_tile;
}

// Instance's methods
void PaintArea::onPaint(wxPaintEvent& event) {
    assert(m_gridController != nullptr);
    SetClientSize(
        m_gridController->getColsCount() * m_gridController->getCellsSize(),
        m_gridController->getRowsCount() * m_gridController->getCellsSize()
    );

    cv::Scalar colors[5] = {cv::Scalar(255, 255, 0), cv::Scalar(255, 0, 0), cv::Scalar(0, 255, 0), cv::Scalar(0, 0, 255), cv::Scalar(0, 255, 255)};
    wxPaintDC dc(this);

    std::vector<Tile> tiles = m_gridController->getTiles();
    int i = 0;
    for(Tile tile: tiles) {
        drawTile(dc, tile);
    }

    for(int r = 0; r < m_gridController->getRowsCount(); r++) {
        for(int c = 0; c < m_gridController->getColsCount(); c++) {
            int j = 0;
            while(j < tiles.size() && !tiles[j].cellIn(r, c)) {
                j++;
            }

            if(j == tiles.size()) {
                drawCell(dc, r, c);
            }
        }
    }

    if(m_selectRect.GetTopLeft() != wxPoint(-1, -1) && m_selectRect.GetBottomRight() != wxPoint(-1, -1)) {
        dc.SetBrush(SELECTION_BRUSH);

        dc.DrawRectangle(m_selectRect);
    }
}

void PaintArea::drawTile(wxPaintDC& dc, const Tile& tile) {
    wxPoint topLeft(tile.getColMin() * m_gridController->getCellsSize(), tile.getRowMin() * m_gridController->getCellsSize());
    wxSize size(tile.getWitdh() * m_gridController->getCellsSize(), tile.getHeight() * m_gridController->getCellsSize());

    if(tile.getImage() == nullptr) {
        wxRect rect(topLeft, size);
        wxBrush brush = dc.GetBrush();
        if(rect.Intersects(m_selectRect) || (m_selectedTile != nullptr && m_selectedTile->getId() == tile.getId())) {
            dc.SetBrush(wxBrush(wxColour(200, 200, 200)));
        }

        dc.DrawRectangle(rect);
        dc.SetBrush(brush);
    } else {
        cv::Mat resized;
        cv::resize(tile.getImage()->getData(), resized, 
        cv::Size(tile.getWitdh() * m_gridController->getCellsSize(), tile.getHeight() * m_gridController->getCellsSize()));

        cv::Mat rgb;
        cv::cvtColor(resized, rgb, cv::COLOR_BGR2RGB);

        wxImage image(rgb.cols, rgb.rows, rgb.data, true);
        wxBitmap bmp(image);
        dc.DrawBitmap(bmp, topLeft);
    }
}

void PaintArea::drawCell(wxPaintDC& dc, int row, int col) {
    wxPoint topLeft(col * m_gridController->getCellsSize(), row * m_gridController->getCellsSize());
    wxSize size(m_gridController->getCellsSize(), m_gridController->getCellsSize());

    wxRect rect(topLeft, size);
    wxBrush brush = dc.GetBrush();
    if(rect.Intersects(m_selectRect)) {
        dc.SetBrush(wxBrush(wxColour(200, 200, 200)));
    }

    dc.DrawRectangle(rect);
    dc.SetBrush(brush);
}