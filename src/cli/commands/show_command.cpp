#include "cli/commands/show_command.hpp"
#include <iostream>

// Static variables
static const std::string S_SEPARATOR = "| ";

// Helpers functions
std::string fillVoid(int value, int maxLength) {
    std::string str = std::to_string(value);
    if(str.length() < maxLength) {
        return std::string(maxLength - str.length(), ' ');
    } else {
        return "";
    }

}

std::string fillVoid(const std::string& str, int maxLength) {
    if(str.length() < maxLength) {
        return std::string(maxLength - str.length(), ' ');
    } else {
        return "";
    }

}

// Constructors
ShowCmd::ShowCmd(std::vector<std::string> args): m_args(args) {
}

// Destructor

// Getters

// Setters

// Instance's methods
void ShowCmd::execute(CLI *p_cli) {
    try {
        switch (m_args.size())
        {
        case 1:
            if(m_args[0] == "-i" || m_args[0] == "--images") {
                // Shows the list of loaded images
                showImages(p_cli);
            } else if(m_args[0] == "-t" || m_args[0] == "--tiles") {
                showTiles(p_cli);
            } else {
                throw std::exception();
            }
            break;
        
        default:
            throw std::exception();
        }
    } catch(...) {
        std::cout << "invalid command" << std::endl;
    }
}

void ShowCmd::showImages(CLI *p_cli) {
    ImagesController *p_imagesController = p_cli->getImagesController();
    Image *p_lastImage = p_imagesController->getImagesCount() > 0 ? p_imagesController->getImages()[p_imagesController->getImagesCount() - 1]: nullptr;

    const int NB_SPACES_ID = p_lastImage != nullptr ? std::to_string(p_lastImage->getId()).length() : 2;
    
    int NB_SPACES_FILE_NAME = 0;
    for(Image *p_image: p_imagesController->getImages()) {
        if(p_image->getFileName().length() > NB_SPACES_FILE_NAME) {
            NB_SPACES_FILE_NAME = p_image->getFileName().length();
        }
    }
    NB_SPACES_FILE_NAME -= std::string("file name").length();

    const std::string ID_HEADER = "id" + std::string(NB_SPACES_ID - 1, ' ');
    const std::string FILE_NAME_HEADER = "file name" + std::string(NB_SPACES_FILE_NAME, ' ');

    const std::string INFOS = ID_HEADER + S_SEPARATOR + FILE_NAME_HEADER;

    std::cout << INFOS << std::endl;
    std::cout << std::string(INFOS.length(), '=') << std::endl;

    for(Image *p_image: p_cli->getImagesController()->getImages()) {
        std::cout << p_image->getId() << fillVoid(p_image->getId(), ID_HEADER.length()) << S_SEPARATOR;
        std::cout << p_image->getFileName() << fillVoid(p_image->getFileName(), FILE_NAME_HEADER.length()) << std::endl;
    }
}

void ShowCmd::showTiles(CLI *p_cli) {
    GridController *p_gridController = p_cli->getGridController();

    const int NB_SPACES = p_gridController->getTilesCount() > 0 ? 
    std::to_string(p_gridController->getTiles()[p_gridController->getTilesCount() - 1].getId()).length() + 1 
    : 2;

    const std::string ID_HEADER = "id" + std::string(NB_SPACES - 1, ' ');

    const int MAX_ROWS = std::to_string(p_gridController->getRowsCount()).length();
    const int MAX_COLS = std::to_string(p_gridController->getColsCount()).length();

    const std::string ROW_MIN_HEADER = "row min" + std::string(MAX_ROWS, ' ');
    const std::string COL_MIN_HEADER = "col min" + std::string(MAX_COLS, ' ');
    const std::string ROW_MAX_HEADER = "row max" + std::string(MAX_ROWS, ' ');
    const std::string COL_MAX_HEADER = "col max" + std::string(MAX_COLS, ' ');

    const std::string infos = ID_HEADER + S_SEPARATOR + ROW_MIN_HEADER + S_SEPARATOR + COL_MIN_HEADER + S_SEPARATOR + ROW_MAX_HEADER + S_SEPARATOR + COL_MAX_HEADER;

    std::cout << infos << std::endl;
    std::cout << std::string(infos.length(), '=') << std::endl;

    for(Tile tile: p_cli->getGridController()->getTiles()) {
        std::cout << tile.getId() << fillVoid(tile.getId(), ID_HEADER.length()) << S_SEPARATOR;
        std::cout << tile.getRowMin() << fillVoid(tile.getRowMin(), ROW_MIN_HEADER.length()) << S_SEPARATOR;
        std::cout << tile.getColMin() << fillVoid(tile.getColMin(), COL_MIN_HEADER.length()) << S_SEPARATOR;
        std::cout << tile.getRowMax() << fillVoid(tile.getRowMax(), ROW_MAX_HEADER.length()) << S_SEPARATOR;
        std::cout << tile.getColMax() << fillVoid(tile.getColMax(), COL_MAX_HEADER.length()) << std::endl;
    }
}