#include "controllers/images_controller.hpp"
#include "controllers/workspace_controller.hpp"
#include <exception>
#include <array>

/**
 * ImagesListener
 */
void ImagesListener::onImageLoaded(Image *p_image) {
}

void ImagesListener::onImageNotLoaded(const std::string& filePath) {
}

void ImagesListener::onImageDeleted(Image image) {
}

/**
 * ImagesController
 */
// Static variables
/**
 * The array of the supported files extensions.
 */
static const std::array<std::string, 5> S_SUPPORTED_EXTENSIONS = {"png", "jpg", "jpeg", "jpe", "webp"};

// Implementations helper functions
/**
 * Function used to sort the vector of images.
 */
bool compareImages(Image *p_image1, Image *p_image2) {
    return p_image1->getId() < p_image2->getId();
}

/**
 * Compare two image to checks if there are the same.
 * 
 * @param img1 an image
 * @param img2 an image
 * @returns true if the two images are the same image, else false.
 */
bool sameImage(const cv::Mat& img1, const cv::Mat& img2) {
    if(img1.size() != img2.size()) {
        return false;
    }
    return !cv::norm(img1, img2, cv::NORM_L1);
}

// Constructors
ImagesController::ImagesController() {
}

// Destructor
ImagesController::~ImagesController() {
    for(Image *p_image: m_images) {
        delete p_image;
    }
    m_images.clear();
}

// Getters
int ImagesController::getImagesCount() const {
    return m_images.size();
}

Image* ImagesController::getImage(int id) const {
    int i = 0;
    while(i < m_images.size() && m_images[i]->getId() != id) {
        i++;
    }

    return i < m_images.size() ? m_images[i] : nullptr;
}

std::vector<Image*> ImagesController::getImages() const {
    return m_images;
}

// Setters

// Instance's methods
void ImagesController::addImagesListener(ImagesListener *p_imagesListener) {
    if(p_imagesListener != nullptr) {
        m_listeners.push_back(p_imagesListener);
    }
}

void ImagesController::removeImagesListener(ImagesListener *p_imagesListener) {
    if(p_imagesListener == nullptr) {
        return;
    }

    int i = 0;
    while(i < m_listeners.size() && m_listeners[i] != p_imagesListener) {
        i++;
    }

    if(i < m_listeners.size()) {
        m_listeners.erase(m_listeners.begin() + i);
    }
}

void ImagesController::load(const std::vector<std::string>& filesPaths) {
    for(const auto& filePath: filesPaths) {
        // Extraction of the file extension
        std::string fileExt = filePath.substr(filePath.find_last_of(".") + 1);
        
        // Check the file extension is supported
        int i = 0;
        while(i < S_SUPPORTED_EXTENSIONS.size() && S_SUPPORTED_EXTENSIONS[i] != fileExt) {
            i++;
        }

        if(i < S_SUPPORTED_EXTENSIONS.size()) {
            // Supported file extension
            cv::Mat data = cv::imread(filePath, cv::IMREAD_ANYCOLOR);

            if(!data.empty()) {
                // Image successfully loaded
                i = 0;
                while(i < m_images.size() && !sameImage(m_images[i]->getData(), data)) {
                    i++;
                }

                if(i == m_images.size()) {
                    // Not a duplicate of an already loaded image
                    // Search for the first id available
                    i = 0;
                    int id = 0;
                    while(i < m_images.size() && m_images[i]->getId() == id) {
                        id = m_images[i]->getId() + 1;
                        i++;
                    }

                    // Extraction of the file name
                    std::string fileName = filePath.substr(filePath.find_last_of("/") + 1);

                    Image *p_image = new Image(id, fileName, data);
                    m_images.push_back(p_image);
                    std::sort(m_images.begin(), m_images.end(), compareImages);

                    for(ImagesListener *p_listener: m_listeners) {
                        p_listener->onImageLoaded(p_image);
                    }
                }

                continue;
            }
        }

        // Unsupported file extension or image could not be loaded
        for(ImagesListener *p_listener: m_listeners) {
            p_listener->onImageNotLoaded(filePath);
        }
    }
}

void ImagesController::remove(int id) {
    int i = 0;
    while(i < m_images.size() && m_images[i]->getId() != id) {
        i++;
    }

    if(i < m_images.size()) {
        // Image successfully removed
        Image image(*m_images[i]);

        for(ImagesListener *p_listener: m_listeners) {
            p_listener->onImageDeleted(image);
        }
        delete m_images[i];
        m_images.erase(m_images.begin() + i);
    } else {
        // No image with the given id
        throw std::out_of_range("");
    }
}

void ImagesController::removeAll() {
    for(Image *p_image: m_images) {
        Image image(*p_image);

        for(ImagesListener *p_listener: m_listeners) {
            p_listener->onImageDeleted(image);
        }
        delete p_image;
    }
    m_images.clear();
}

void ImagesController::loadFromWorkspace(std::ifstream& workspace) {
    int nbImages = readInt(workspace);

    std::vector<Image*> images;
    for(int i = 0; i < nbImages; i++) {
        int id = readInt(workspace);
        std::string fileName = readStr(workspace);

        int rows = readInt(workspace);
        int cols = readInt(workspace);
        int type = readInt(workspace);
        cv::Mat mat(rows, cols, type);

        workspace.read((char*) mat.data, mat.total() * mat.elemSize());

        Image *p_image = new Image(id, fileName, mat);
        images.push_back(p_image);
    }

    removeAll();

    m_images = images;
    for(Image *p_image: m_images) {
        for(ImagesListener *p_listener: m_listeners) {
            p_listener->onImageLoaded(p_image);
        }
    }
}

void ImagesController::saveInWorkspace(std::ofstream& workspace) {
    writeInt(workspace, getImagesCount());

    for(Image *p_image: m_images) {
        writeInt(workspace, p_image->getId());
        writeStr(workspace, p_image->getFileName());

        cv::Mat mat = p_image->getData();
        writeInt(workspace, mat.rows);
        writeInt(workspace, mat.cols);
        writeInt(workspace, mat.type());

        workspace.write((char*) mat.data, mat.total() * mat.elemSize());
    }
}