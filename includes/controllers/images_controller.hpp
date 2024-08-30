#ifndef IMAGES_CONTROLLER_HPP
#define IMAGES_CONTROLLER_HPP

#include "model/images.hpp"
#include <vector>
#include <fstream>

/**
 * The listener abstract class to receive images events.
 * 
 * Each objects of this class need to be registered to an ImagesController's object (using the method addImagesListener) to receive events.
 */
class ImagesListener {
public:

    /**
     * Invoked when a new image has been loaded.
     * 
     * @param p_image a pointer to the new loaded image.
     */
    virtual void onImageLoaded(Image *p_image);

    /**
     * Invoked when an image could not be loaded.
     * 
     * @param filePath the file path of the image.
     */
    virtual void onImageNotLoaded(const std::string& filePath);

    /**
     * Invoked when an image has been deleted.
     * 
     * @param image a copy of the deleted image.
     */
    virtual void onImageDeleted(Image image);
};

/**
 * The controller class used to manages images inside the application.
 * 
 * Each object of this class can generated images events, those events can be received by objects implementing the 
 * ImagesListener class after they are registered to an ImagesController's object using the method addImagesListener.
 */
class ImagesController {
public:

    // Constructors
    ImagesController();

    // Destructor
    ~ImagesController();

    // Getters
    /**
     * Returns the number of images currently loaded with this object.
     * 
     * @return the number of images currently loaded with this object.
     */
    int getImagesCount() const;

    /**
     * Returns the image with the specified id, else nullptr.
     * 
     * @param id an image id.
     * @return a pointer to the image with the specified id, else nullptr.
     */
    Image* getImage(int id) const;

    /**
     * Returns a list of pointers to all the loaded images in this object.
     * 
     * @return a list of pointers to the loaded images in this object.
     */
    std::vector<Image*> getImages() const;

    // Setters

    // Instance's methods
    /**
     * Registers a new object implementing the ImagesListener class to receive images events from this object.
     * 
     * @param p_imagesListener a pointer the object to register.
     */
    void addImagesListener(ImagesListener *p_imagesListener);

    /**
     * Unregisters an already registered object implementing the ImagesListener class to stop receiving images events from this object.
     * 
     * @param p_imagesListener a pointer of the object to unregister.
     */
    void removeImagesListener(ImagesListener *p_imagesListener);

    /**
     * Loads new images, generates an onImageLoaded event for each image successfully loaded,
     * else generates an onImageNotLoaded event.
     * 
     * @param filesPaths the list of the files paths (relative or absolute) of the images to load.
     */
    void load(const std::vector<std::string>& filesPaths);

    /**
     * Deletes an image loaded in this object using its id. 
     * Raise an out_of_range exception if there no image with the specified id.
     * Generates an onImageDeleted event if the image has been deleted.
     * 
     * @param id an image id.
     */
    void remove(int id);

    /**
     * Deletes every image loaded in this object. 
     * Generates an onImageDeleted event for each image.
     */
    void removeAll();

    /**
     * Loads the content of a workspace.
     * 
     * @param workspace a stream to read from the workspace.
     */
    void loadFromWorkspace(std::ifstream& workspace);

    /**
     * Writes the current state of this controller in a workspace.
     * 
     * @param workspace a stream to write in the workspace.
     */
    void saveInWorkspace(std::ofstream& workspace);

private:

    std::vector<Image*> m_images;

    std::vector<ImagesListener*> m_listeners;
};

#endif