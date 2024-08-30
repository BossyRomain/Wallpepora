#ifndef LOAD_COMMAND_HPP
#define LOAD_COMMAND_HPP

#include "cli/commands/command.hpp"
#include "controllers/images_controller.hpp"
#include <vector>

/**
 * This command loads new images, it accepts file paths (relative or absolute) and directory paths (relative or absolute).
 * When using a directory path, all the elements in the directory will try to be loaded, even if they are not images files.
 */
class LoadCmd: public Command, public ImagesListener {
public:

    // Constructors
    /**
     * Constructs a load command with its arguments.
     * 
     * @param args - a list of file paths (relative or absolute) and/or a list of directory paths (relative or absolute).
     */
    LoadCmd(std::vector<std::string> args);

    // Destructor

    // Getters

    // Setters

    // Instance's methods
    void onImageLoaded(Image *p_image) override;

    void onImageNotLoaded(const std::string& filePath) override;

    void execute(CLI *p_cli) override;

private:

    // Instance's methods
    void loadImages(ImagesController *p_imagesController);
    
    void loadWorkspace(WorkspaceController *p_workspaceController, const std::string& filePath);

    // Attributes
    std::vector<std::string> m_args;

    int m_nbImagesLoaded;
};

#endif