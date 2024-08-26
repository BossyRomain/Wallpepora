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