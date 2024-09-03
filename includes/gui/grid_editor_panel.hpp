#ifndef GRID_EDITOR_WINDOW_HPP
#define GRID_EDITOR_WINDOW_HPP

#include <wx/wx.h>
#include <wx/dnd.h>
#include "controllers/grid_controller.hpp"
#include "controllers/images_controller.hpp"
#include "gui/grid_painter.hpp"
#include "gui/images_panel.hpp"

/**
 * The panel inside the GUI which permits the user :
 * - to merge cells into tiles
 * - to unmerge tiles into cells
 * - to place images in the tile on the grid
 */
class GridEditorPanel: public wxPanel, public GridListener {
public:

    // Constructors
    GridEditorPanel();

    // Destructor
    ~GridEditorPanel();

    // Getters
    GridController* getGridController() const;

    ImagesController* getImagesController() const;

    // Setters
    void setGridController(GridController *p_gridController);

    void setImagesController(ImagesController *p_imagesController);

    // Instance's methods
    void onRowsUpdated(int rows) override;

    void onColsUpdated(int cols) override;

    void onCellsSizeUpdated(int size) override;

    void onTileCreated(const Tile *p_tile) override;

    void onTileDeleted(Tile tile) override;

    void onImagePlaced(const Tile *p_tile, const Image *p_image) override;

    void Init();

    /**
     * Invoked when the user press the left button of his mouse.
     */
    void onSelectionBegin(wxMouseEvent& event);

    /**
     * Invoked when the user release the left button of his mouse.
     */
    void onSelectionEnd(wxMouseEvent& event);

    /**
     * Invoked when the user drops an image on the grid.
     */
    void onImageDropped(wxCoord x, wxCoord y, int image_id);

private:
    // Instance's methods
    /**
     * Invoked when the grid's dimensions are updated.
     * Update the virtual size of the wxScrolledWindow containing the PaintArea's object attribute of this object.
     */
    void sizedScrolledWindow(wxPaintEvent& event);

    /**
     * Invoked when the mouse cursor moves on the grid.
     */
    void onMouseMotion(wxMouseEvent& event);
    
    /**
     * Invoked when the user clicks on the button to merge cells.
     */
    void merge(wxCommandEvent& event);

    /**
     * Invoked when the user clicks on the button to unmerge a tile.
     */
    void unmerge(wxCommandEvent& event);

    /**
     * Invoked when the user clicks on the button to generate a new wallpaper.
     */
    void generate(wxCommandEvent& event);

    /**
     * Invoked when the user clicks on the zoom in button.
     */
    void onZoomIn(wxCommandEvent& event);

    /**
     * Invoked when the user clicks on the zoom out button.
     */
    void onZoomOut(wxCommandEvent& event);

    /**
     * Invoked when the user clicks on the button to fill the empty cells.
     */
    void onFillSoft(wxCommandEvent& event);

    /**
     * Invoked when the user clicks on the button to fill every cells.
     */
    void onFillHard(wxCommandEvent& event);

    /**
     * Invoked when the user clicks on the button to remove all the images on the grid.
     */
    void onRemoveImages(wxCommandEvent& event);

    /**
     * Invoked when the user clicks on the button to reset the grid.
     */
    void onResetGrid(wxCommandEvent& event);
    
    // Attributes
    GridController *m_gridController;

    ImagesController *m_imagesController;

    wxScrolledWindow *m_scrolledWindow;

    GridPainter *m_paintArea;

    wxPoint m_startSelection;

    wxPoint m_endSelection;

    int m_oldRows;

    int m_oldCols;
};

class GridEditorPanelXmlHandler : public wxXmlResourceHandler
{
public:
    // Constructor.
    GridEditorPanelXmlHandler();
 
    // Creates the control and returns a pointer to it.
    virtual wxObject *DoCreateResource();
 
    // Returns true if we know how to create a control for the given node.
    virtual bool CanHandle(wxXmlNode *node);
 
    // Register with wxWidgets' dynamic class subsystem.
    wxDECLARE_DYNAMIC_CLASS(GridEditorPanelXmlHandler);
};


#endif