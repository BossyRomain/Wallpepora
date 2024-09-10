#include "gui/grid_painter.hpp"
#include "gui/gui_utils.hpp"
#include <opencv2/opencv.hpp>
#include <map>

// Static variables
static const wxBrush SELECTION_BRUSH(wxColour(254, 254, 250, 150));

// Helpers functions
wxBitmap getEmptyBmp(int width, int height) {
    wxBitmap bmp(width, height);
    wxMemoryDC dc(bmp);
    dc.SetBrush(*wxWHITE_BRUSH);

    wxRect rect(0, 0, width, height);
    dc.DrawRectangle(rect);

    return bmp;   
}

/******************************************************
 ******************************************************
 ***                                                ***
 ***                 GridPainter                    ***
 ***                                                ***
 ******************************************************
 ******************************************************/
// Constructors
GridPainter::GridPainter(): m_gridController(nullptr), m_selectRect(S_NO_SELECTION), m_selectedTile(nullptr), m_zoom(1.0f) {}

// Destructor
GridPainter::~GridPainter() {
    m_gridController->removeGridListener(this);
}

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
    return static_cast<int>(m_zoom * m_gridController->getCellsSize());
}

// Setters
void GridPainter::setGridController(GridController *p_gridController) {
    if(m_gridController != nullptr) {
        m_gridController->removeGridListener(this);
    }

    m_gridController = p_gridController;
    m_gridController->addGridListener(this);
    onCellsSizeUpdated(m_gridController->getCellsSize());
}

void GridPainter::setSelecRect(wxRect selection) {
    m_selectRect = selection;
    Refresh();
}

void GridPainter::setSelectedTile(const Tile *p_tile) {
    m_selectedTile = p_tile;
    Refresh();
}

void GridPainter::setZoom(float zoom) {
    m_zoom = zoom;
    Refresh();
}

// Instance's methods
void GridPainter::onRowsUpdated(int rows) {
    int cellsSize = m_gridController->getCellsSize();
    int oldRows = m_bmp.GetHeight() / cellsSize;
    wxBitmap oldBmp = m_bmp;

    m_bmp = wxBitmap(oldBmp.GetWidth(), rows * cellsSize);
    wxMemoryDC dc(m_bmp);
    dc.DrawBitmap(oldBmp, 0, 0);

    if(rows >= oldRows) {
        wxBitmap emptyCellBmp = getEmptyBmp(cellsSize, cellsSize);
        for(int r = oldRows; r < rows; r++) {
            for(int c = 0; c < m_gridController->getColsCount(); c++) {
                dc.DrawBitmap(emptyCellBmp, c * cellsSize, r * cellsSize);
            }
        }
    }
    Refresh();
}

void GridPainter::onColsUpdated(int cols) {
    int cellsSize = m_gridController->getCellsSize();
    int oldCols = m_bmp.GetWidth() / cellsSize;
    wxBitmap oldBmp = m_bmp;

    m_bmp = wxBitmap(cols * cellsSize, oldBmp.GetHeight());
    wxMemoryDC dc(m_bmp);
    dc.DrawBitmap(oldBmp, 0, 0);

    if(cols >= oldCols) {
        wxBitmap emptyCellBmp = getEmptyBmp(cellsSize, cellsSize);
        for(int c = oldCols; c < cols; c++) {
            for(int r = 0; r < m_gridController->getRowsCount(); r++) {
                dc.DrawBitmap(emptyCellBmp, c * cellsSize, r * cellsSize);
            }
        }
    }
    Refresh();
}

void GridPainter::onCellsSizeUpdated(int size) {
    int cellsSize = m_gridController->getCellsSize();
    m_bmp = wxBitmap(m_gridController->getColsCount() * cellsSize, m_gridController->getRowsCount() * cellsSize);
    wxMemoryDC dc(m_bmp);

    std::vector<Tile> tiles = m_gridController->getTiles();
    for(Tile tile: tiles) {
        int width = tile.getWidth() * cellsSize;
        int height = tile.getHeight() * cellsSize;
        int x = tile.getColMin() * cellsSize;
        int y = tile.getRowMin() * cellsSize;

        wxBitmap bmp;
        if(tile.getImage() != nullptr) {
            bmp = toBmp(tile.getImage()->getData(), width, height);
        } else {
            bmp = getEmptyBmp(width, height);
        }
        dc.DrawBitmap(bmp, x, y);
    }

    wxBitmap emptyCellBmp = getEmptyBmp(cellsSize, cellsSize);
    for(int r = 0; r < m_gridController->getRowsCount(); r++) {
        for(int c = 0; c < m_gridController->getColsCount(); c++) {
            if(m_gridController->getTileAt(r, c) == nullptr) {
                dc.DrawBitmap(emptyCellBmp, c * cellsSize, r * cellsSize);
            }
        }
    }
    Refresh();
}

void GridPainter::onTileCreated(const Tile *p_tile) {
    int cellsSize = m_gridController->getCellsSize();
    wxMemoryDC dc(m_bmp);
    int x = p_tile->getColMin() * cellsSize;
    int y = p_tile->getRowMin() * cellsSize;
    int width = p_tile->getWidth() * cellsSize;
    int height = p_tile->getHeight() * cellsSize;

    dc.DrawBitmap(getEmptyBmp(width, height), x, y);
    Refresh();       
}

void GridPainter::onTileResized(const Tile *p_tile) {
    int cellsSize = m_gridController->getCellsSize();
    wxMemoryDC dc(m_bmp);
    int x = p_tile->getColMin() * cellsSize;
    int y = p_tile->getRowMin() * cellsSize;
    int width = p_tile->getWidth() * cellsSize;
    int height = p_tile->getHeight() * cellsSize;

    wxBitmap bmp;
    if(p_tile->getImage() != nullptr) {
        bmp = toBmp(p_tile->getImage()->getData(), width, height);
    } else {
        bmp = getEmptyBmp(width, height);
    }
    dc.DrawBitmap(bmp, x, y);
    Refresh();
}

void GridPainter::onTileDeleted(Tile tile) {
    int cellsSize = m_gridController->getCellsSize();
    wxMemoryDC dc(m_bmp);
    int x = tile.getColMin() * cellsSize;
    int y = tile.getRowMin() * cellsSize;

    wxBitmap emptyCellBmp = getEmptyBmp(cellsSize, cellsSize);
    for(int r = 0; r < tile.getHeight(); r++) {
        for(int c = 0; c < tile.getWidth(); c++) {
            dc.DrawBitmap(emptyCellBmp, x + c * cellsSize, y + r * cellsSize);
        }
    }
    Refresh();
}

void GridPainter::onImagePlaced(const Tile *p_tile, const Image *p_image) {
    int cellsSize = m_gridController->getCellsSize();
    wxMemoryDC dc(m_bmp);
    int x = p_tile->getColMin() * cellsSize;
    int y = p_tile->getRowMin() * cellsSize;
    int width = p_tile->getWidth() * cellsSize;
    int height = p_tile->getHeight() * cellsSize;

    wxBitmap bmp;
    if(p_image != nullptr) {
        bmp = toBmp(p_image->getData(), width, height);
    } else {
        bmp = getEmptyBmp(width, height);
    }

    dc.DrawBitmap(bmp, x, y);
    Refresh();
}

void GridPainter::onPaint(wxPaintEvent& event) {
    if(m_gridController == nullptr) {
        return;
    }
    
    SetClientSize(m_gridController->getColsCount() * getCellsSize(), m_gridController->getRowsCount() * getCellsSize());
    // recalculate();

    wxPaintDC dc(this);
    dc.SetUserScale(m_zoom, m_zoom);

    dc.DrawBitmap(m_bmp, 0, 0);

    dc.SetUserScale(1.0, 1.0);

    if(m_selectRect.GetTopLeft() != wxPoint(-1, -1) && m_selectRect.GetBottomRight() != wxPoint(-1, -1)) {
        dc.SetBrush(SELECTION_BRUSH);
        dc.DrawRectangle(m_selectRect);
    }
}

void GridPainter::drawTile(wxPaintDC& dc, wxPoint pos, wxBitmap bmp) {
    dc.DrawBitmap(bmp, pos);
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







/******************************************************
 ******************************************************
 ***                                                ***
 ***            GridPainterXmlHandler               ***
 ***                                                ***
 ******************************************************
 ******************************************************/
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