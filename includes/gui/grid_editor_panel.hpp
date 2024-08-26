#ifndef GRID_EDITOR_WINDOW_HPP
#define GRID_EDITOR_WINDOW_HPP

#include <wx/wx.h>
#include <wx/dnd.h>
#include "controllers/grid_controller.hpp"
#include "controllers/images_controller.hpp"
#include "gui/paint_area.hpp"
#include "gui/images_panel.hpp"

/**
 * The panel inside the GUI which permits the user :
 * - to merge cells into tiles
 * - to unmerge tiles into cells
 * - to place images in the tile on the grid
 */
class GridEditorPanel: public wxPanel {
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
    void onImageDroped(wxCoord x, wxCoord y, int image_id);

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
     * Invoked when the user changes the zoom.
     */
    void onZoom(wxCommandEvent& event);

    /**
     * Invoked when the user clicks on the button to fill the empty cells.
     */
    void onFillSoft(wxCommandEvent& event);

    /**
     * Invoked when the user clicks on the button to fill every cells.
     */
    void onFillHard(wxCommandEvent& event);
    
    // Attributes
    GridController *m_gridController;

    ImagesController *m_imagesController;

    wxScrolledWindow *m_scrolledWindow;

    PaintArea *m_paintArea;

    wxPoint m_startSelection;

    wxPoint m_endSelection;
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