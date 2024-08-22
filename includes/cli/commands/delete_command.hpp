#ifndef DELETE_COMMAND_HPP
#define DELETE_COMMAND_HPP

#include "cli/commands/command.hpp"
#include "controllers/images_controller.hpp"

/**
 * This command remove one image using its id or every loaded images.
 * 
 * When removing one image using its id, an error message is showed if the id given is not 
 * the id of an existing image.
 */
class DeleteCmd: public Command, public ImagesListener {
public:

    // Constructors
    DeleteCmd();

    DeleteCmd(int imageId);

    // Destructor

    // Getters

    // Setters

    // Instance's methods
    void onImageDeleted(Image p_image) override;

    void execute(CLI *p_cli) override;

private:

    int m_imageId;

    bool m_deleteAll;

    int m_nbImagesDeleted;
};

#endif