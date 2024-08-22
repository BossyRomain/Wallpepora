#include "cli/commands/delete_command.hpp"
#include <iostream>
#include <exception>

bool confirmAction(const std::string& msg) {
    std::cout << msg << std::endl;
    std::string answer;
    std::getline(std::cin, answer);

    return answer == "y" || answer == "yes";
}

// Constructors
DeleteCmd::DeleteCmd(): m_imageId(-1), m_deleteAll(true) {
}

DeleteCmd::DeleteCmd(int imageId): m_imageId(imageId), m_deleteAll(false) {
}

// Destructor

// Getters

// Setters

// Instance's methods
void DeleteCmd::onImageDeleted(Image p_image) {
    m_nbImagesDeleted++;
}

void DeleteCmd::execute(CLI *p_cli) {
    if(!confirmAction("This action can't be canceled. Are you sure ? (y/n)")) {
        return;
    }

    m_nbImagesDeleted = 0;
    p_cli->getImagesController()->addImagesListener(this);
    if(m_deleteAll) {
        // Delete all the images
        int imagesCount = p_cli->getImagesController()->getImagesCount();
        
        p_cli->getImagesController()->removeAll();

        std::cout << m_nbImagesDeleted << "/" << imagesCount << " images deleted" << std::endl;
    } else {
        // Delete one image
        try {
            p_cli->getImagesController()->remove(m_imageId);
            if(m_nbImagesDeleted == 1) {
                std::cout << "the image with the id " << m_imageId << " has been removed" << std::endl;
            } else {
                std::cout << "failed to remove the image with the id " << m_imageId << std::endl;
            }
        } catch(std::out_of_range& e) {
            std::cout << "there is no image with the id " << m_imageId << std::endl;
        }
    }
    p_cli->getImagesController()->removeImagesListener(this);
}