#ifndef MAIN_FRAME_HPP
#define MAIN_FRAME_HPP

#include <wx/wx.h>
#include "controllers/workspace_controller.hpp"

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
    WorkspaceController* getWorkspaceController() const;

    // Setters
    void setWorkspaceController(WorkspaceController *p_workspaceController);

    // Instance's methods

private:

    // Instance's methods
    void load(wxCommandEvent& event);

    void save(wxCommandEvent& event);

    // Attributes
    WorkspaceController *m_workspaceController;
};

#endif