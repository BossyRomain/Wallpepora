#include "controllers/images_controller.hpp"
#include "controllers/grid_controller.hpp"
#include "controllers/wallpapers_controller.hpp"
#include "cli/cli.hpp"
#include "gui/main_frame.hpp"
#include "gui/images_panel.hpp"
#include "gui/grid_params_panel.hpp"
#include "gui/grid_editor_panel.hpp"
#include "gui/wallpapers_panel.hpp"
#include <iostream>
#include <wx/wx.h>
#include <wx/xrc/xmlres.h>
#include <wx/xrc/xh_all.h>

/**
 * Class used for the GUI (needed by wxWidgets).
 */
class App: public wxApp {
public:

    App(ImagesController *p_imagesController, GridController *p_gridController, WallpapersController *p_wallpapersController);

    bool OnInit() override;

private:

    ImagesController *m_imagesController;

    GridController *m_gridController;

    WallpapersController *m_wallpapersController;
};

App::App(ImagesController *p_imagesController, GridController *p_gridController, WallpapersController *p_wallpapersController): 
m_imagesController(p_imagesController), m_gridController(p_gridController), m_wallpapersController(p_wallpapersController) {
}

bool App::OnInit() {
    assert(m_imagesController != nullptr);
    assert(m_gridController != nullptr);

    wxXmlResource::Get()->InitAllHandlers();
    wxXmlResource::Get()->LoadAllFiles("./res/ui/");
    wxXmlResource::Get()->LoadAllFiles("./res/icons/");

    MainFrame *p_mainFrame = new MainFrame();
    wxPanel *p_gridPanel = XRCCTRL(*p_mainFrame, "grid_page", wxPanel);
    wxPanel *p_wallpapersPage = XRCCTRL(*p_mainFrame, "wallpapers_page", wxPanel);

    ImagesPanel *p_imagesPanel = new ImagesPanel(p_gridPanel);
    p_imagesPanel->setImagesController(m_imagesController);

    GridEditorPanel *p_gridEditorPanel = new GridEditorPanel(p_gridPanel);
    p_gridEditorPanel->setGridController(m_gridController);
    p_gridEditorPanel->setImagesController(m_imagesController);

    GridParamsPanel *p_gridParamsPanel = new GridParamsPanel(p_gridPanel);
    p_gridParamsPanel->setGridController(m_gridController);
    p_gridParamsPanel->setGridEditorPanel(p_gridEditorPanel);

    WallpapersPanel *p_wallpapersPanel = new WallpapersPanel(p_wallpapersPage);
    p_wallpapersPanel->setWallpapersController(m_wallpapersController);

    p_mainFrame->init(p_imagesPanel, p_gridParamsPanel, p_gridEditorPanel, p_wallpapersPanel);    
    p_mainFrame->Show(true);

    return true;
}

int main(int argc, char* argv[]) {
    ImagesController *p_imagesController = new ImagesController();
    GridController *p_gridController = new GridController();
    WallpapersController *p_wallpapersController = new WallpapersController();

    p_gridController->setWallpapersController(p_wallpapersController);

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
        cli.run();
    } else {
        // Launching the application with the gui
        wxApp::SetInstance(new App(p_imagesController, p_gridController, p_wallpapersController));
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
}