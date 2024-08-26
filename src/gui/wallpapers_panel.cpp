#include "gui/wallpapers_panel.hpp"
#include "gui/gui_utils.hpp"
#include <wx/xrc/xh_all.h>
#include <wx/xrc/xmlres.h>
#include <wx/filedlg.h>

#define THUMBNAIL_SIZE 300

// Constructors
WallpapersPanel::WallpapersPanel(): m_wallpapersController(nullptr) {
}

// Destructor
WallpapersPanel::~WallpapersPanel() {
}

// Getters

WallpapersController* WallpapersPanel::getWallpapersController() const {
    return m_wallpapersController;
}

// Setters
void WallpapersPanel::setWallpapersController(WallpapersController *p_wallpapersController) {
    if(m_wallpapersController != nullptr) {
        m_wallpapersController->removeWallpapersListener(this);
    }
    m_wallpapersController = p_wallpapersController;
    m_wallpapersController->addWallpapersListener(this);
}

// Instance's methods
void WallpapersPanel::Init() {
    m_wallpapersList = new wxImageList(THUMBNAIL_SIZE, THUMBNAIL_SIZE);

    m_listCtrl = XRCCTRL(*this, "wallpapers_list", wxListCtrl);
    m_listCtrl->InsertColumn(0, "", wxLIST_FORMAT_LEFT, THUMBNAIL_SIZE);
    m_listCtrl->AssignImageList(m_wallpapersList, wxIMAGE_LIST_SMALL);

    wxButton *p_exportBtn = XRCCTRL(*this, "export_btn", wxButton);

    m_display = XRCCTRL(*this, "wallpaper_display", wxStaticBitmap);

    m_listCtrl->Bind(wxEVT_LIST_ITEM_SELECTED, &WallpapersPanel::onWallpaperSelected, this);
    p_exportBtn->Bind(wxEVT_BUTTON, &WallpapersPanel::exportWallpaper, this);
}

void WallpapersPanel::onWallpaperGenerated(cv::Mat wallpaper) {
    wxBitmap bmp = createThumbnail(wallpaper, THUMBNAIL_SIZE, THUMBNAIL_SIZE);

    long imgId = m_wallpapersList->Add(bmp);
    m_listCtrl->InsertItem(m_listCtrl->GetItemCount(), "", imgId);
}

void WallpapersPanel::onWallpaperSelected(wxListEvent& event) {
    int id = event.GetIndex();

    cv::Mat wallpaper = m_wallpapersController->getWallpaper(id);
    wxBitmap bmp = createThumbnail(wallpaper, wallpaper.cols, wallpaper.rows);

    m_display->SetBitmap(bmp);
    Refresh();
}

void WallpapersPanel::exportWallpaper(wxCommandEvent& event) {
    wxFileDialog fd(this, "Export", "~", "", "Images files (*.png;*.jpg;*.jpeg;*.jpe;*.webp)|*.png;*.jpg;*.jpeg;*.jpe;*.webp",
    wxFD_SAVE|wxFD_OVERWRITE_PROMPT);

    if(fd.ShowModal() != wxID_CANCEL) {
        m_wallpapersController->exportWallpaper(fd.GetPath().ToStdString(), m_listCtrl->GetNextItem(-1, wxLIST_NEXT_ALL, wxLIST_STATE_SELECTED));
    }
}




wxIMPLEMENT_DYNAMIC_CLASS(WallpapersPanelXmlHandler, wxXmlResourceHandler);
 
WallpapersPanelXmlHandler::WallpapersPanelXmlHandler()
{
    AddWindowStyles();
}
 
wxObject *WallpapersPanelXmlHandler::DoCreateResource()
{
    XRC_MAKE_INSTANCE(control, WallpapersPanel)
 
    control->Create(m_parentAsWindow, GetID(), GetPosition(), GetSize(), GetStyle(), GetName());
    CreateChildren(control);
    control->Init();

    SetupWindow(control);
 
    return control;
}
 
bool WallpapersPanelXmlHandler::CanHandle(wxXmlNode *node)
{
    return IsOfClass(node, wxT("WallpapersPanel"));
}