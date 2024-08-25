#include "gui/main_frame.hpp"
#include <wx/xrc/xmlres.h>
#include <wx/gbsizer.h>
#include <wx/notebook.h>

// Constructors
MainFrame::MainFrame() {
    wxXmlResource::Get()->LoadFrame(this, nullptr, "main_frame");
    Maximize(true);
}

// Destructor
MainFrame::~MainFrame() {
    
}

// Getters

// Setters

// Instance's methods
void MainFrame::init(ImagesPanel *p_imagesPanel, GridParamsPanel *p_gridParamsPanel, 
GridEditorPanel *p_gridEditorPanel, WallpapersPanel *p_wallpapersPanel) {
    wxPanel *p_gridPage = XRCCTRL(*this, "grid_page", wxPanel);
    wxGridBagSizer *gridEditorSizer = (wxGridBagSizer*) p_gridPage->GetSizer();

    gridEditorSizer->Add(p_gridParamsPanel, wxGBPosition(0, 0), wxDefaultSpan, wxEXPAND);
    gridEditorSizer->Add(p_gridEditorPanel, wxGBPosition(0, 1), wxDefaultSpan, wxEXPAND);
    gridEditorSizer->Add(p_imagesPanel, wxGBPosition(0, 2), wxDefaultSpan, wxEXPAND);

    gridEditorSizer->AddGrowableRow(0);
    gridEditorSizer->AddGrowableCol(1, 5);

    wxPanel *p_wallpapersPage = XRCCTRL(*this, "wallpapers_page", wxPanel);
    wxGridBagSizer *p_wallpapersPageSizer = (wxGridBagSizer*) p_wallpapersPage->GetSizer();
    p_wallpapersPageSizer->Add(p_wallpapersPanel, wxGBPosition(0, 0), wxDefaultSpan, wxEXPAND);

    p_wallpapersPageSizer->AddGrowableRow(0);
    p_wallpapersPageSizer->AddGrowableCol(0);
}