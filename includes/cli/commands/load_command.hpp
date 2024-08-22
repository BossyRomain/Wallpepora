#ifndef LOAD_COMMAND_HPP
#define LOAD_COMMAND_HPP

#include "cli/commands/command.hpp"
#include "controllers/images_controller.hpp"
#include <vector>

/**
 * This command loads new images, it accepts files paths (relative or absolute) and directories paths (relative or absolute).
 * When using a directory path, all the elements inside the directory will try to be loaded, even if they are not images files.
 */
class LoadCmd: public Command, public ImagesListener {
public:

    // Constructors
    LoadCmd(std::vector<std::string> args);

    // Destructor

    // Getters

    // Setters

    // Instance's methods
    void onImageLoaded(Image *p_image) override;

    void onImageNotLoaded(const std::string& filePath) override;

    void execute(CLI *p_cli) override;

private:

    std::vector<std::string> m_args;

    int m_nbImagesLoaded;
};

#endif