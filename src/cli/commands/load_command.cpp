#include "cli/commands/load_command.hpp"
#include <filesystem>
namespace fs = std::filesystem;

// Constructors
LoadCmd::LoadCmd(std::vector<std::string> args): m_args(args) {}

// Destructor

// Getters

// Setters

// Instance's methods
void LoadCmd::onImageLoaded(Image *p_image) {
    m_nbImagesLoaded++;
}

void LoadCmd::onImageNotLoaded(const std::string& filePath) {
    std::cout << "failed to load the image " << filePath << std::endl;
}

void LoadCmd::execute(CLI *p_cli) {
    assert(p_cli != nullptr);
    assert(p_cli->getImagesController() != nullptr);
    assert(p_cli->getWorkspaceController() != nullptr);

    if(m_args.size() == 2 && m_args[0] == "-w") {
        loadWorkspace(p_cli->getWorkspaceController(), m_args[1]);
    } else {
        loadImages(p_cli->getImagesController());
    }
}

void LoadCmd::loadImages(ImagesController *p_imagesController) {
    assert(p_imagesController != nullptr);
    std::vector<std::string> filesPaths;

    for(std::string arg: m_args) {
        std::string path = "";
        if(arg[0] == '~') {
            path = std::getenv("HOME") + arg.substr(1);
        } else {
            path = arg;
        }

        if(fs::is_directory(path)) {
            // The argument is a directory
            for(auto& file: fs::directory_iterator(path)) {
                filesPaths.push_back(file.path());
            }
        } else {
            // The argument is a file
            filesPaths.push_back(path);
        }
    }

    const int nbToLoad = filesPaths.size();
    m_nbImagesLoaded = 0;
    p_imagesController->addImagesListener(this);
    p_imagesController->load(filesPaths);
    p_imagesController->removeImagesListener(this);

    std::cout << "successfully load " << m_nbImagesLoaded << "/" << nbToLoad << " images" << std::endl;
}

void LoadCmd::loadWorkspace(WorkspaceController *p_workspaceController, const std::string& filePath) {
    assert(p_workspaceController != nullptr);
    std::string path = filePath;
    if(path[0] == '~') {
        path = std::getenv("HOME") + filePath.substr(1);
    }

    p_workspaceController->load(path);
}