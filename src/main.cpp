#include "controllers/images_controller.hpp"
#include "controllers/grid_controller.hpp"
#include "cli/cli.hpp"
#include "gui/main_frame.hpp"
#include "gui/images_panel.hpp"
#include "gui/grid_params_panel.hpp"
#include "gui/grid_editor_panel.hpp"
#include <iostream>
#include <wx/wx.h>
#include <wx/xrc/xmlres.h>
#include <wx/xrc/xh_all.h>

/**
 * Class used for the GUI (needed by wxWidgets).
 */
class App: public wxApp {
public:

    App(ImagesController *p_imagesController, GridController *p_gridController);

    bool OnInit() override;

private:

    ImagesController *m_imagesController;

    GridController *m_gridController;
};

App::App(ImagesController *p_imagesController, GridController *p_gridController): 
m_imagesController(p_imagesController), m_gridController(p_gridController) {
}

bool App::OnInit() {
    assert(m_imagesController != nullptr);
    assert(m_gridController != nullptr);

    wxXmlResource::Get()->InitAllHandlers();
    wxXmlResource::Get()->LoadAllFiles("./res/ui/");
    wxXmlResource::Get()->LoadAllFiles("./res/icons/");

    MainFrame *p_mainFrame = new MainFrame();

    ImagesPanel *p_imagesPanel = new ImagesPanel(p_mainFrame);
    p_imagesPanel->setImagesController(m_imagesController);

    GridEditorPanel *p_gridEditorPanel = new GridEditorPanel(p_mainFrame);
    p_gridEditorPanel->setGridController(m_gridController);
    p_gridEditorPanel->setImagesController(m_imagesController);

    GridParamsPanel *p_gridParamsPanel = new GridParamsPanel(p_mainFrame);
    p_gridParamsPanel->setGridController(m_gridController);
    p_gridParamsPanel->setGridEditorPanel(p_gridEditorPanel);    

    wxGridBagSizer *sizer = (wxGridBagSizer*) p_mainFrame->GetSizer();
    sizer->Add(p_gridParamsPanel, wxGBPosition(0, 0), wxDefaultSpan, wxEXPAND);
    sizer->Add(p_gridEditorPanel, wxGBPosition(0, 1), wxDefaultSpan, wxEXPAND);
    sizer->Add(p_imagesPanel, wxGBPosition(0, 2), wxDefaultSpan, wxEXPAND);

    sizer->AddGrowableCol(1, 5);

    p_mainFrame->Show(true);

    return true;
}

int main(int argc, char* argv[]) {
    ImagesController *p_imagesController = new ImagesController();
    GridController *p_gridController = new GridController();

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
        cli.run();
    } else {
        // Launching the application with the gui
        wxApp::SetInstance(new App(p_imagesController, p_gridController));
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
}