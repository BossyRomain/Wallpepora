#ifndef IMAGES_PANEL_HPP
#define IMAGES_PANEL_HPP

#include <wx/wx.h>
#include <wx/listctrl.h>
#include "controllers/images_controller.hpp"

/**
 * The panel inside the GUI which permits the user :
 * - to loads new images
 * - show the list of loaded images
 * - to delete an image
 * - to delete all images in one action
 */
class ImagesPanel: public wxPanel, public ImagesListener {
public:

    // Constructors
    ImagesPanel(wxWindow *p_parent);

    // Destructor
    ~ImagesPanel();

    // Getters
    ImagesController* getImagesController() const;

    // Setters
    void setImagesController(ImagesController *p_imagesController);

    // Instance's methods
    void onImageLoaded(Image *p_image) override;

    void onImageDeleted(Image image) override;

private:

    // Events handlers
    /**
     * Invoked when the button to load new images is clicked.
     * Opens a files dialog so the user choose which files to load.
     * Does nothing if the user select no file.
     */
    void loadImages(wxCommandEvent& event);

    /**
     * Invoked when the user select an image in the list of images. 
     */
    void onImageSelected(wxListEvent& event);

    /**
     * Invoked when the user press the key DELETE on his keyboard.
     * Remove the selected image if there is one, else does nothing.
     * Asks for the confirmation of the action.
     */
    void onDeleteImage(wxKeyEvent& event);

    /**
     * Invoked when the button to delete all the images is clicked.
     * Asks for the confirmation of the action.
     */
    void onDeleteAllImages(wxCommandEvent& event);

    // Attributes
    ImagesController *m_imagesController;

    wxListCtrl *m_listCtrl;

    wxImageList *m_imagesList;

    int m_selectedImage;
};

#endif