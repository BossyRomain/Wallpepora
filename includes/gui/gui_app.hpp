#ifndef GUI_APP_HPP
#define GUI_APP_HPP

#include <wx/wx.h>
#include "gui/images_panel.hpp"
#include "gui/grid_params_panel.hpp"
#include "gui/grid_editor_panel.hpp"
#include "gui/wallpapers_panel.hpp"
#include "controllers/workspace_controller.hpp"

/**
 * Class used for the GUI (needed by wxWidgets).
 */
class GUIApp: public wxApp {
public:

    // Constructors
    GUIApp(ImagesController *p_imagesController, GridController *p_gridController, 
    WallpapersController *p_wallpapersController, WorkspaceController *p_workspaceController);

    // Destructor

    // Getters

    // Setters

    // Instance's methods
    bool OnInit() override;

private:

    ImagesController *m_imagesController;

    GridController *m_gridController;

    WallpapersController *m_wallpapersController;

    WorkspaceController *m_workspaceController;
};

#endif