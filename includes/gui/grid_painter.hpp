#ifndef PAINT_AREA_HPP
#define PAINT_AREA_HPP

#include <wx/wx.h>
#include <wx/xrc/xh_all.h>
#include <wx/xrc/xmlres.h>
#include "controllers/grid_controller.hpp"

const static wxRect S_NO_SELECTION(wxPoint(-1, -1), wxSize(0, 0));

/**
 * Draw the current state of the grid inside the GUI.
 * Also draw other elements like the rectangle of selection when the user selects cells to merge.
 */
class GridPainter: public wxPanel, public GridListener {
public:

    // Constructors
    GridPainter();

    // Destructor
    ~GridPainter();

    // Getters
    GridController* getGridController() const;

    wxRect getSelectRect() const;

    const Tile* getSelectedTile() const;

    float getZoom() const;

    int getCellsSize() const;

    // Setters
    void setGridController(GridController *p_gridController);

    void setSelecRect(wxRect selection);

    void setSelectedTile(const Tile *p_tile);

    void setZoom(float zoom);

    // Instance's methods
    void onRowsUpdated(int rows) override;

    void onColsUpdated(int cols) override;

    void onCellsSizeUpdated(int size) override;

    void onTileCreated(const Tile *p_tile) override;

    void onTileResized(const Tile *p_tile) override;

    void onTileDeleted(Tile tile) override;

    void onImagePlaced(const Tile *p_tile, const Image *p_image) override;

    /**
     * Invoked when the GUI is refreshed.
     */
    void onPaint(wxPaintEvent& event);

private:

    // Instance's methods
    /**
     * Draws a tile.
     */
    void drawTile(wxPaintDC& dc, wxPoint pos, wxBitmap tile);

    /**
     * Draws a cell.
     */
    void drawCell(wxPaintDC& dc, int row, int col);

    // Attributes
    GridController *m_gridController;

    wxRect m_selectRect;

    const Tile *m_selectedTile;

    float m_zoom;

    wxBitmap m_bmp;
};

class GridPainterXmlHandler : public wxXmlResourceHandler
{
public:
    // Constructor.
    GridPainterXmlHandler();
 
    // Creates the control and returns a pointer to it.
    virtual wxObject *DoCreateResource();
 
    // Returns true if we know how to create a control for the given node.
    virtual bool CanHandle(wxXmlNode *node);
 
    // Register with wxWidgets' dynamic class subsystem.
    wxDECLARE_DYNAMIC_CLASS(GridPainterXmlHandler);
};

#endif