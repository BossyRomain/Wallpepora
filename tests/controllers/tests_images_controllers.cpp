#include <gtest/gtest.h>
#include <vector>
#include <random>
#include "fixtures.hpp"
#include "controllers/images_controller.hpp"

class TestImageListener: public ImagesListener {
public:

    // Constructors

    // Destructor

    // Getters
    std::vector<Image*> getLoadedImages() const;

    std::vector<std::string> getLoadingFailedImages() const;

    std::vector<Image> getDeletedImages() const;

    // Setters

    // Instance's methods
    void onImageLoaded(Image *p_image) override;

    void onImageNotLoaded(const std::string& filePath) override;

    void onImageDeleted(Image image) override;

private:

    std::vector<Image*> m_loadedImages;

    std::vector<std::string> m_loadingFailedImages;

    std::vector<Image> m_deletedImages;
};

// Constructors

// Destructor

// Getters
std::vector<Image*> TestImageListener::getLoadedImages() const {
    return m_loadedImages;
}

std::vector<std::string> TestImageListener::getLoadingFailedImages() const {
    return m_loadingFailedImages;
}

std::vector<Image> TestImageListener::getDeletedImages() const {
    return m_deletedImages;
}

// Setters

// Instance's methods
void TestImageListener::onImageLoaded(Image *p_image) {
    m_loadedImages.push_back(p_image);
}

void TestImageListener::onImageNotLoaded(const std::string& filePath) {
    m_loadingFailedImages.push_back(filePath);
}

void TestImageListener::onImageDeleted(Image image) {
    m_deletedImages.push_back(image);
}

/*********************
 ** Tests           **
 *********************
 */

/**
 * Checks that it is possible to load valids images
 */
TEST_F(TestsImagesPaths, TestValidsImagesLoading) {
    TestImageListener listener;
    ImagesController controller;

    controller.addImagesListener(&listener);
    controller.load(getValidsImagesPaths());

    ASSERT_EQ(listener.getLoadedImages().size(), getValidsImagesPaths().size());
    ASSERT_EQ(listener.getLoadingFailedImages().size(), 0);
}

/**
 * Checks that it is impossible to load invalids images
 */
TEST_F(TestsImagesPaths, TestInvalidsImagesLoading) {
    TestImageListener listener;
    ImagesController controller;

    controller.addImagesListener(&listener);
    controller.load(getInvalidsImagesPaths());

    ASSERT_EQ(listener.getLoadedImages().size(), 0);
    ASSERT_EQ(listener.getLoadingFailedImages().size(), getInvalidsImagesPaths().size());
}

/**
 * Checks that it is impossible to load the same image twice
 */
TEST_F(TestsImagesPaths, TestDuplicatesLoading) {
    TestImageListener listener;
    ImagesController controller;

    controller.addImagesListener(&listener);
    controller.load(getValidsImagesPaths());
    controller.load(getValidsImagesPaths());

    ASSERT_EQ(listener.getLoadedImages().size(), getValidsImagesPaths().size());
    ASSERT_EQ(listener.getLoadingFailedImages().size(), 0);
}

/**
 * A mix of the three previous test
 */
TEST_F(TestsImagesPaths, TestGlobalLoading) {
    TestImageListener listener;
    ImagesController controller;

    std::vector<std::string> validsPaths(getValidsImagesPaths());
    std::vector<std::string> invalidsPaths(getInvalidsImagesPaths());

    std::vector<std::string> filesPaths;
    filesPaths.insert(filesPaths.end(), validsPaths.begin(), validsPaths.end());
    filesPaths.insert(filesPaths.end(), validsPaths.begin(), validsPaths.end());
    filesPaths.insert(filesPaths.end(), invalidsPaths.begin(), invalidsPaths.end());

    std::shuffle(filesPaths.begin(), filesPaths.end(), std::default_random_engine());

    controller.addImagesListener(&listener);
    controller.load(filesPaths);

    ASSERT_EQ(listener.getLoadedImages().size(), validsPaths.size());
    ASSERT_EQ(listener.getLoadingFailedImages().size(), invalidsPaths.size());
}

/**
 * Checks that each loaded image has a unique id
 */
TEST_F(TestsImagesPaths, TestUniqueIds) {
    ImagesController controller;
    controller.load(getValidsImagesPaths());

    std::vector<Image*> imgs = controller.getImages();
    for(int i = 0; i < imgs.size(); i++) {
        for(int j = i + 1; j < imgs.size(); j++) {
            ASSERT_NE(imgs[i]->getId(), imgs[j]->getId());
        }
    }
}

/**
 * Checks that it is possible to remove a loaded image using its id
 */
TEST_F(TestsImagesPaths, TestRemoveImage) {
    ImagesController controller;

    controller.load(getValidsImagesPaths());
    controller.remove(4);

    std::vector<Image*> imgs = controller.getImages();
    int i = 0;
    while(i < imgs.size() && imgs[i]->getId() != 4) {
        i++;
    }

    ASSERT_EQ(i, imgs.size());
}

/**
 * Checks that it is possible to remove all loaded images in one action
 */
TEST_F(TestsImagesPaths, TestRemoveAllImages) {
    ImagesController controller;

    controller.load(getValidsImagesPaths());
    controller.removeAll();

    ASSERT_EQ(controller.getImagesCount(), 0);
    ASSERT_EQ(controller.getImages().size(), 0);
}

/**
 * Checks that an out_of_range exception is raised when trying to remove an non existing image
 */
TEST_F(TestsImagesPaths, TestRemoveImageNonExisting) {
    ImagesController controller;

    controller.load(getValidsImagesPaths());
    controller.remove(4);

    try {
        controller.remove(4);
        FAIL();
    } catch(std::out_of_range& e) {
    }

    try {
        controller.remove(-1);
        FAIL();
    } catch(std::out_of_range& e) {
    }
}