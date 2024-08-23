#ifndef GRID_EDITOR_WINDOW_HPP
#define GRID_EDITOR_WINDOW_HPP

#include <wx/wx.h>
#include "controllers/grid_controller.hpp"

class PaintArea: public wxPanel {
public:

    // Constructors
    PaintArea(wxWindow *p_parent);

    // Destructor

    // Getters
    GridController* getGridController() const;

    // Setters
    void setGridController(GridController *p_gridController);

    // Instance's methods
    void onPaint(wxPaintEvent& event);

private:

    GridController *m_gridController;
};


class GridEditorPanel: public wxPanel {
public:

    // Constructors
    GridEditorPanel(wxWindow *p_parent);

    // Destructor
    ~GridEditorPanel();

    // Getters
    GridController* getGridController() const;

    // Setters
    void setGridController(GridController *p_gridController);

    // Instance's methods

private:
    // Instance's methods
    void sizedScrolledWindow(wxPaintEvent& event);

    // Attributes
    GridController *m_gridController;

    wxScrolledWindow *p_scrolledWindow;

    PaintArea *p_paintArea;
};

#endif