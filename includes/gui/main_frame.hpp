#ifndef MAIN_FRAME_HPP
#define MAIN_FRAME_HPP

#include <wx/wx.h>
#include "gui/images_panel.hpp"
#include "gui/grid_editor_panel.hpp"
#include "gui/grid_params_panel.hpp"
#include "gui/wallpapers_panel.hpp"

/**
 * The main frame of the GUI.
 */
class MainFrame: public wxFrame {
public:

    // Constructors
    MainFrame();

    // Destructor
    ~MainFrame();

    // Getters

    // Setters

    // Instance's methods
    void init(ImagesPanel *p_imagesPanel, GridParamsPanel *p_gridParamsPanel, 
    GridEditorPanel *p_gridEditorPanel, WallpapersPanel *p_wallpapersPanel);

private:

};

#endif