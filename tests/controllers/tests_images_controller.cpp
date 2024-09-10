#include <gtest/gtest.h>
#include "fixtures.hpp"
#include "controllers/images_controller.hpp"
#include <vector>
#include <random>


/**
 * Tests loading of valid images.
 */
TEST_F(ImagesFixture, TestLoadingValid) {
    int nbImgs = getValidImgsPaths().size();
    p_imgsController->load(getValidImgsPaths());

    // All the images should be loaded
    ASSERT_EQ(p_imgsController->getImagesCount(), nbImgs);
    ASSERT_EQ(p_imgsListener->getLoadedImgs().size(), nbImgs);

    ASSERT_TRUE(p_imgsListener->getLoadingFailedImgs().empty());
}

/**
 * Tests all loaded images have unique id.
 */
TEST_F(ImagesFixture, TestLoadedImgsIds) {
    p_imgsController->load(getValidImgsPaths());

    std::vector<Image*> imgs = p_imgsController->getImages();
    for(int i = 0; i < imgs.size(); i++) {
        for(int j = i + 1; j < imgs.size(); j++) {
            ASSERT_NE(imgs[i]->getId(), imgs[j]->getId());
        }
    }
}

/**
 * Tests it is impossible to load the same image twice.
 */
TEST_F(ImagesFixture, TestLoadingDuplicate) {
    int nbImgs = getValidImgsPaths().size();
    p_imgsController->load(getValidImgsPaths());

    std::vector<std::string> paths = getValidImgsPaths();
    std::shuffle(paths.begin(), paths.end(), std::default_random_engine(time(nullptr)));

    p_imgsController->load(paths);

    ASSERT_EQ(p_imgsController->getImagesCount(), nbImgs);
    ASSERT_EQ(p_imgsListener->getLoadedImgs().size(), nbImgs);
}

/**
 * Tests it is impossible to load invalid images.
 */
TEST_F(ImagesFixture, TestLoadingInvalid) {
    int nbImgs = getInvalidImgsPaths().size();
    p_imgsController->load(getInvalidImgsPaths());

    ASSERT_EQ(p_imgsController->getImagesCount(), 0);
    ASSERT_EQ(p_imgsListener->getLoadingFailedImgs().size(), nbImgs);
}

/**
 * Tests when trying to load valid and invalid images at the same time, only the valid ones are loaded.
 */
TEST_F(ImagesFixture, TestLoadingMix) {
    std::vector<std::string> paths = getAllPaths();
    std::shuffle(paths.begin(), paths.end(), std::default_random_engine(time(nullptr)));

    p_imgsController->load(paths);

    ASSERT_EQ(p_imgsController->getImagesCount(), getValidImgsPaths().size());
    ASSERT_EQ(p_imgsListener->getLoadedImgs().size(), getValidImgsPaths().size());
    ASSERT_EQ(p_imgsListener->getLoadingFailedImgs().size(), getInvalidImgsPaths().size());
}

/**
 * Tests to remove a loaded image using its id.
 */
TEST_F(ImagesFixture, TestRemoveImageExisting) {
    int nbImgs = getValidImgsPaths().size();
    p_imgsController->load(getValidImgsPaths());

    int nbToRemove = rand() % (nbImgs / 2);

    for(int nbRemoved = 1; nbRemoved <= nbToRemove; nbRemoved++) {
        int rand = random() % p_imgsController->getImagesCount();
        int imgId = p_imgsController->getImages()[rand]->getId();

        p_imgsController->remove(imgId);
        ASSERT_EQ(p_imgsController->getImagesCount(), nbImgs - nbRemoved);

        ASSERT_EQ(p_imgsListener->getDeletedImgs().size(), nbRemoved);
        ASSERT_EQ(p_imgsListener->getDeletedImgs()[nbRemoved - 1].getId(), imgId);
    }
}

/**
 * Tests that an out_of_range exception is raised when trying to remove a non existing image using its id.
 */
TEST_F(ImagesFixture, TestRemoveNonExisting) {
    p_imgsController->load(getValidImgsPaths());

    p_imgsController->remove(4);

    EXPECT_THROW(p_imgsController->remove(4), std::out_of_range);
    EXPECT_THROW(p_imgsController->remove(-1), std::out_of_range);
    int id = p_imgsController->getImages()[p_imgsController->getImagesCount() - 1]->getId() + 1;
    EXPECT_THROW(p_imgsController->remove(id), std::out_of_range);
}
/**
 * Tests it is possible to remove all the loaded image in one action.
 */
TEST_F(ImagesFixture, TestRemoveAll) {
    p_imgsController->load(getValidImgsPaths());

    p_imgsController->removeAll();

    ASSERT_EQ(p_imgsController->getImagesCount(), 0);
    ASSERT_EQ(p_imgsListener->getDeletedImgs().size(), getValidImgsPaths().size());
}