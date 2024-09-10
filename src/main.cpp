#include "controllers/images_controller.hpp"
#include "controllers/grid_controller.hpp"
#include "controllers/wallpapers_controller.hpp"
#include "controllers/workspace_controller.hpp"
#include "cli/cli.hpp"
#include "gui/gui_app.hpp"
#include <iostream>
#include <wx/wx.h>
#include <wx/xrc/xmlres.h>
#include <wx/xrc/xh_all.h>

int main(int argc, char* argv[]) {
    ImagesController *p_imagesController = new ImagesController();
    GridController *p_gridController = new GridController();
    WallpapersController *p_wallpapersController = new WallpapersController();
    WorkspaceController *p_workspaceController = new WorkspaceController();

    p_imagesController->addImagesListener(p_gridController);

    p_gridController->setWallpapersController(p_wallpapersController);

    p_workspaceController->setImagesController(p_imagesController);
    p_workspaceController->setGridController(p_gridController);

    bool cli = false;
    if(argc == 2) {
        std::string arg = argv[1];
        cli = arg == "--no-gui";
    }

    if(cli) {
        // Launching the application with the cli
        CLI cli;

        cli.setImagesController(p_imagesController);
        cli.setGridController(p_gridController);
        cli.setWallpapersController(p_wallpapersController);
        cli.setWorkspaceController(p_workspaceController);
        cli.run();
    } else {
        // Launching the application with the gui
        std::string execPath(argv[0]);
        std::string resFolderPath = execPath.substr(0, execPath.find_last_of("/")) + "/res";

        wxApp::SetInstance(new GUIApp(resFolderPath, p_imagesController, p_gridController, p_wallpapersController, p_workspaceController));
        wxEntryStart(argc, argv);

        // Check if wxApp initialized successfully
        if (!wxTheApp->CallOnInit())
        {
            // If initialization failed, clean up and exit
            wxTheApp->OnExit();
            wxEntryCleanup();
            return 1;
        }

        // Start the main event loop
        int returnCode = wxTheApp->OnRun();

        // Clean up and exit the application
        wxTheApp->OnExit();
        wxEntryCleanup();
    }

    delete p_imagesController;
    delete p_gridController;
    delete p_wallpapersController;
    delete p_workspaceController;
}