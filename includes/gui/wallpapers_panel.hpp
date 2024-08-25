#ifndef WALLPAPERS_PANEL_HPP
#define WALLPAPERS_PANEL_HPP

#include <wx/wx.h>
#include <wx/listctrl.h>
#include "controllers/wallpapers_controller.hpp"

class WallpapersPanel: public wxPanel, public WallpapersListener {
public:

    // Constructors
    WallpapersPanel(wxWindow *p_parent);

    // Destructor
    ~WallpapersPanel();

    // Getters
    WallpapersController* getWallpapersController() const;

    // Setters
    void setWallpapersController(WallpapersController *p_wallpapersController);

    // Instance's methods
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

#endif