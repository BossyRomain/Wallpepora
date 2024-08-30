#ifndef DELETE_COMMAND_HPP
#define DELETE_COMMAND_HPP

#include "cli/commands/command.hpp"
#include "controllers/images_controller.hpp"

/**
 * This command removes one image using its id or all loaded images.
 * 
 * When removing one image using its id, an error message is shown if there is no image
 * with the specified id.
 */
class DeleteCmd: public Command, public ImagesListener {
public:

    // Constructors
    /**
     * Constructs a delete command to delete all loaded images.
     */
    DeleteCmd();

    /**
     * Constructs a delete command to delete one image using its id.
     */
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