#include "gui/images_panel.hpp"
#include "gui/gui_utils.hpp"
#include <wx/xrc/xh_all.h>
#include <wx/xrc/xmlres.h>
#include <wx/filedlg.h>
#include <wx/msgdlg.h>
#include <wx/dnd.h>
#include <opencv2/opencv.hpp>
#include <vector>
#include <iostream>

/***
 * ImagesPanel
 */
#define THUMBNAIL_SIZE 300

// Constructors
ImagesPanel::ImagesPanel(): m_imagesController(nullptr) {
}

// Destructor
ImagesPanel::~ImagesPanel() {
}

// Getters
ImagesController* ImagesPanel::getImagesController() const {
    return m_imagesController;
}

// Setters
void ImagesPanel::setImagesController(ImagesController *p_imagesController) {
    if(m_imagesController != nullptr) {
        m_imagesController->removeImagesListener(this);
    }
    m_imagesController = p_imagesController;
    m_imagesController->addImagesListener(this);
}

// Instance's methods
void ImagesPanel::Init() {
    wxButton *p_loadBtn = XRCCTRL(*this, "load_btn", wxButton);
    p_loadBtn->Bind(wxEVT_BUTTON, &ImagesPanel::loadImages, this);

    wxButton *p_deleteAllBtn = XRCCTRL(*this, "delete_all_btn", wxButton);
    p_deleteAllBtn->Bind(wxEVT_BUTTON, &ImagesPanel::onDeleteAllImages, this);

    m_imagesList = new wxImageList(THUMBNAIL_SIZE, THUMBNAIL_SIZE);
    m_listCtrl = XRCCTRL(*this, "images_list", wxListCtrl);

    m_listCtrl->InsertColumn(0, "", wxLIST_FORMAT_LEFT, THUMBNAIL_SIZE);
    m_listCtrl->AssignImageList(m_imagesList, wxIMAGE_LIST_SMALL);

    m_listCtrl->Bind(wxEVT_CHAR_HOOK, &ImagesPanel::onDeleteImage, this);
    m_listCtrl->Bind(wxEVT_LIST_BEGIN_DRAG, &ImagesPanel::onDragStart, this);
}

void ImagesPanel::onImageLoaded(Image *p_image) {
    cv::Mat data = p_image->getData();

    wxBitmap bmp = createThumbnail(data, THUMBNAIL_SIZE, THUMBNAIL_SIZE);
    long imgId = m_imagesList->Add(bmp);
    m_listCtrl->InsertItem(m_listCtrl->GetItemCount(), wxString(std::to_string(p_image->getId())), imgId);
}

void ImagesPanel::onImageDeleted(Image image) {
    long id = m_listCtrl->FindItem(0, wxString(std::to_string(image.getId())));

    m_listCtrl->DeleteItem(id);
}

// Events handlers
void ImagesPanel::loadImages(wxCommandEvent& event) {
    wxFileDialog fd(this, "Load", "~", "", "Images files (*.png;*.jpg;*.jpeg;*.jpe;*.webp)|*.png;*.jpg;*.jpeg;*.jpe;*.webp",
    wxFD_OPEN|wxFD_MULTIPLE|wxFD_FILE_MUST_EXIST);

    if(fd.ShowModal() != wxID_CANCEL) {
        // The user has selected at least one file
        wxArrayString arrayString;
        fd.GetPaths(arrayString);

        std::vector<std::string> filesPaths;
        for(wxString str: arrayString) {
            filesPaths.push_back(str.ToStdString());
        }

        m_imagesController->load(filesPaths);
    }
}

void ImagesPanel::onDeleteImage(wxKeyEvent& event) {
    long selectedIndex = m_listCtrl->GetNextItem(-1, wxLIST_NEXT_ALL, wxLIST_STATE_SELECTED);
    if(selectedIndex >= 0 && event.GetKeyCode() == WXK_DELETE) {
        wxMessageDialog dg(this, "This action will delete the selected image and can't be canceled. Are you sure ?", "", wxYES_NO|wxNO_DEFAULT);
        
        if(dg.ShowModal() == wxID_YES) {
            wxListItem item;
            item.SetId(selectedIndex);
            m_listCtrl->GetItem(item);
            int imgId;
            item.GetText().ToInt(&imgId);
            m_imagesController->remove(imgId);
        }
    }
}

void ImagesPanel::onDeleteAllImages(wxCommandEvent& event) {
    wxMessageDialog dg(this, "This action will delete all the images and can't be canceled. Are you sure ?", "", wxYES_NO|wxNO_DEFAULT);

    if(dg.ShowModal() == wxID_YES) {
        m_imagesController->removeAll();
    }
}

void ImagesPanel::onDragStart(wxListEvent& event) {
    long selectedIndex = m_listCtrl->GetNextItem(-1, wxLIST_NEXT_ALL, wxLIST_STATE_SELECTED);
    wxListItem item;
    item.SetId(selectedIndex);
    m_listCtrl->GetItem(item);
    int imgId;
    item.GetText().ToInt(&imgId);

    wxTextDataObject dragData(std::to_string(imgId));
    wxDropSource dragSource(this);
    dragSource.SetData(dragData);
    dragSource.DoDragDrop(wxDrag_CopyOnly);
}





wxIMPLEMENT_DYNAMIC_CLASS(ImagesPanelXmlHandler, wxXmlResourceHandler);
 
ImagesPanelXmlHandler::ImagesPanelXmlHandler()
{
    AddWindowStyles();
}
 
wxObject *ImagesPanelXmlHandler::DoCreateResource()
{
    XRC_MAKE_INSTANCE(control, ImagesPanel)
    
    control->Create(m_parentAsWindow, GetID(), GetPosition(), GetSize(), GetStyle(), GetName());
    CreateChildren(control);
    control->Init();
 
    SetupWindow(control);
 
    return control;
}
 
bool ImagesPanelXmlHandler::CanHandle(wxXmlNode *node)
{
    return IsOfClass(node, wxT("ImagesPanel"));
}