#include "cli/commands/show_command.hpp"

// Constructors
ShowCmd::ShowCmd(std::vector<std::string> args): m_args(args) {
}

// Destructor

// Getters

// Setters

// Instance's methods
void ShowCmd::execute(CLI *p_cli) {
    if(m_args[0] == "-i" || m_args[0] == "--images") {
        // Shows the list of loaded images
        const int NB_SPACES = p_cli->getImagesController()->getImagesCount() > 0 ? 
        std::to_string(p_cli->getImagesController()->getImages()[p_cli->getImagesController()->getImagesCount() - 1]->getId()).length() 
        : 2;

        std::cout << "id" << std::string(NB_SPACES - 1, ' ') << "| file name" << std::endl;
        std::cout << std::string(NB_SPACES + 13, '=') << std::endl;

        for(Image *p_image: p_cli->getImagesController()->getImages()) {
            int idLength = std::to_string(p_image->getId()).length();
            std::cout << p_image->getId() << std::string(NB_SPACES - idLength + 1, ' ')  << "| " << p_image->getFileName() << std::endl;
        }
    }
}