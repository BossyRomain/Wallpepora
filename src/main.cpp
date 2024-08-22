#include "controllers/images_controller.hpp"
#include "cli/cli.hpp"
#include "gui/main_frame.hpp"
#include "gui/images_panel.hpp"
#include <iostream>
#include <wx/wx.h>
#include <wx/xrc/xmlres.h>
#include <wx/xrc/xh_all.h>

/**
 * Class used for the GUI (needed by wxWidgets).
 */
class App: public wxApp {
public:

    App(ImagesController *p_imagesController);

    bool OnInit() override;

private:

    ImagesController *m_imagesController;
};

App::App(ImagesController *p_imagesController): m_imagesController(p_imagesController) {
}

bool App::OnInit() {
    assert(m_imagesController != nullptr);

    wxXmlResource::Get()->InitAllHandlers();
    wxXmlResource::Get()->LoadAllFiles("./res/ui/");

    MainFrame *p_mainFrame = new MainFrame();

    ImagesPanel *p_imagesPanel = new ImagesPanel(p_mainFrame);
    p_imagesPanel->setImagesController(m_imagesController);

    wxGridBagSizer *sizer = (wxGridBagSizer*) p_mainFrame->GetSizer();
    sizer->Add(p_imagesPanel, wxGBPosition(0, 2), wxDefaultSpan, wxEXPAND);

    p_mainFrame->Show(true);

    return true;
}

int main(int argc, char* argv[]) {
    ImagesController *p_imagesController = new ImagesController();

    bool cli = false;
    if(argc == 2) {
        std::string arg = argv[1];
        cli = arg == "--no-gui";
    }

    if(cli) {
        // Launching the application with the cli
        CLI cli;

        cli.setImagesController(p_imagesController);
        cli.run();
    } else {
        // Launching the application with the gui
        wxApp::SetInstance(new App(p_imagesController));
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
}