#include "cli/commands/load_command.hpp"
#include <filesystem>
namespace fs = std::filesystem;

// Constructors
LoadCmd::LoadCmd(std::vector<std::string> args): m_args(args) {
}

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
    p_cli->getImagesController()->addImagesListener(this);
    p_cli->getImagesController()->load(filesPaths);
    p_cli->getImagesController()->removeImagesListener(this);

    std::cout << "successfully load " << m_nbImagesLoaded << "/" << nbToLoad << " images" << std::endl;
}