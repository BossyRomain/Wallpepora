#ifndef WALLPAPERS_PANEL_HPP
#define WALLPAPERS_PANEL_HPP

#include <wx/wx.h>
#include <wx/listctrl.h>
#include <wx/xrc/xh_all.h>
#include <wx/xrc/xmlres.h>
#include "controllers/wallpapers_controller.hpp"

class WallpapersPanel: public wxPanel, public WallpapersListener {
public:

    // Constructors
    WallpapersPanel();

    // Destructor
    ~WallpapersPanel();

    // Getters
    WallpapersController* getWallpapersController() const;

    // Setters
    void setWallpapersController(WallpapersController *p_wallpapersController);

    // Instance's methods
    void Init();

    void onWallpaperGenerated(cv::Mat wallpaper) override;

private:

    // Instance's methods
    void onWallpaperSelected(wxListEvent& event);

    void exportWallpaper(wxCommandEvent& event);

    // Attributes
    WallpapersController *m_wallpapersController;

    wxListCtrl *m_listCtrl;

    wxImageList *m_wallpapersList;

    wxStaticBitmap *m_display;
};

class WallpapersPanelXmlHandler : public wxXmlResourceHandler
{
public:
    // Constructor.
    WallpapersPanelXmlHandler();
 
    // Creates the control and returns a pointer to it.
    virtual wxObject *DoCreateResource();
 
    // Returns true if we know how to create a control for the given node.
    virtual bool CanHandle(wxXmlNode *node);
 
    // Register with wxWidgets' dynamic class subsystem.
    wxDECLARE_DYNAMIC_CLASS(WallpapersPanelXmlHandler);
};

#endif