#include "gui/main_frame.hpp"
#include <wx/xrc/xmlres.h>
#include <wx/filedlg.h>

// Constructors
MainFrame::MainFrame(): m_workspaceController(nullptr) {
    wxXmlResource::Get()->LoadFrame(this, nullptr, "main_frame");

    Bind(wxEVT_MENU, &MainFrame::load, this, XRCID("load_workspace_item"));
    Bind(wxEVT_MENU, &MainFrame::save, this, XRCID("save_workspace_item"));

    Maximize(true);
}

// Destructor
MainFrame::~MainFrame() {
    
}

// Getters
WorkspaceController* MainFrame::getWorkspaceController() const {
    return m_workspaceController;
}

// Setters
void MainFrame::setWorkspaceController(WorkspaceController *p_workspaceController) {
    m_workspaceController = p_workspaceController;
}

// Instance's methods
void MainFrame::load(wxCommandEvent& event) {
    wxFileDialog fd(this, "Load", "~", "", "Workspace files (*.wp)|*.wp",
    wxFD_OPEN|wxFD_FILE_MUST_EXIST);

    if(fd.ShowModal() != wxID_CANCEL) {
        // The user has selected one file
        m_workspaceController->load(fd.GetPath().ToStdString());
        Refresh();
    }
}

void MainFrame::save(wxCommandEvent& event) {
    wxFileDialog fd(this, "Export", "~", "", "Workspace files (*.wp)|*.wp",
    wxFD_SAVE|wxFD_OVERWRITE_PROMPT);

    if(fd.ShowModal() != wxID_CANCEL) {
        m_workspaceController->save(fd.GetPath().ToStdString());
    }
}