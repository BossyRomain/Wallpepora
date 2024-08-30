#include "gui/gui_app.hpp"
#include "gui/main_frame.hpp"
#include "gui/images_panel.hpp"
#include "gui/grid_params_panel.hpp"
#include "gui/grid_editor_panel.hpp"
#include "gui/wallpapers_panel.hpp"

GUIApp::GUIApp(ImagesController *p_imagesController, GridController *p_gridController, WallpapersController *p_wallpapersController, WorkspaceController *p_workspaceController): 
m_imagesController(p_imagesController), m_gridController(p_gridController), m_wallpapersController(p_wallpapersController), m_workspaceController(p_workspaceController) {
}

bool GUIApp::OnInit() {
    assert(m_imagesController != nullptr);
    assert(m_gridController != nullptr);
    assert(m_wallpapersController != nullptr);
    assert(m_workspaceController != nullptr);

    wxXmlResource::Get()->InitAllHandlers();
    wxXmlResource::Get()->AddHandler(new ImagesPanelXmlHandler);
    wxXmlResource::Get()->AddHandler(new WallpapersPanelXmlHandler);
    wxXmlResource::Get()->AddHandler(new GridParamsPanelXmlHandler);
    wxXmlResource::Get()->AddHandler(new GridEditorPanelXmlHandler);
    wxXmlResource::Get()->AddHandler(new GridPainterXmlHandler);

    wxXmlResource::Get()->LoadAllFiles("./res/ui/");

    MainFrame *p_mainFrame = new MainFrame();
    p_mainFrame->setWorkspaceController(m_workspaceController);

    ImagesPanel *p_imagesPanel = XRCCTRL(*p_mainFrame, "images_panel", ImagesPanel);
    p_imagesPanel->setImagesController(m_imagesController);

    GridEditorPanel *p_gridEditorPanel = XRCCTRL(*p_mainFrame, "grid_editor_panel", GridEditorPanel);
    p_gridEditorPanel->setGridController(m_gridController);
    p_gridEditorPanel->setImagesController(m_imagesController);

    GridParamsPanel *p_gridParamsPanel = XRCCTRL(*p_mainFrame, "grid_params_panel", GridParamsPanel);
    p_gridParamsPanel->setGridController(m_gridController);

    WallpapersPanel *p_wallpapersPanel = XRCCTRL(*p_mainFrame, "wallpapers_panel", WallpapersPanel);
    p_wallpapersPanel->setWallpapersController(m_wallpapersController);

    p_mainFrame->Show(true);
    return true;
}