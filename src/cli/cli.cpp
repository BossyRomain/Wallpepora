#include "cli/cli.hpp"
#include "cli/commands/command.hpp"
#include "cli/commands/load_command.hpp"
#include "cli/commands/delete_command.hpp"
#include "cli/commands/show_command.hpp"
#include "cli/commands/set_command.hpp"
#include "cli/commands/merge_command.hpp"
#include "cli/commands/unmerge_command.hpp"
#include <iostream>
#include <vector>
#include <filesystem>
namespace fs = std::filesystem;

enum Commands {
    NONE = 0,
    EXIT,
    LOAD,
    DELETE,
    SET,
    MERGE,
    UNMERGE,
    SHOW
};

// Helper functions
/**
 * Extracts the command from a line entered by the user.
 * 
 * @param line a line entered by the user.
 * @returns the command entered, NONE if no command detected.
 */
Commands extractCommand(const std::string& line) {
    std::string cmd = line.substr(0, line.find_first_of(' '));

    if(cmd == "exit") {
        return EXIT;
    } else if(cmd == "load") {
        return LOAD;
    } else if(cmd == "delete") {
        return DELETE;
    } else if(cmd == "show") {
        return SHOW;
    } else if(cmd == "set") {
        return SET;
    } else if(cmd == "merge") {
        return MERGE;
    } else if(cmd == "unmerge") {
        return UNMERGE;
    }

    return NONE;
}

/**
 * Extracts the arguments of the command entered by the user.
 * 
 * @param line a command entered by the user.
 * @returns the list of the arguments of the command.
 */
std::vector<std::string> extractsArgs(const std::string& line) {
    std::vector<std::string> args;
    if(line.find_first_of(' ') == std::string::npos) {
        return args;
    }

    std::string argsLine = line.substr(line.find_first_of(" ") + 1);
    std::string arg = "";

    for(char c: argsLine) {
        if(c == ' ') {
            args.push_back(arg);
            arg = "";
        } else {
            arg += c;
        }
    }

    if(!arg.empty()) {
        args.push_back(arg);
    }

    return args;
}

// Constructors
CLI::CLI(): m_imagesController(nullptr), m_gridController(nullptr) {
}

// Destructor
CLI::~CLI() {
}

// Getters
ImagesController* CLI::getImagesController() const {
    return m_imagesController;
}

GridController* CLI::getGridController() const {
    return m_gridController;
}

// Setters
void CLI::setImagesController(ImagesController *p_imagesController) {
    m_imagesController = p_imagesController;
}

void CLI::setGridController(GridController *p_gridController) {
    m_gridController = p_gridController;
}

// Instance's methods
int CLI::run() {
    assert(m_imagesController != nullptr);
    assert(m_gridController != nullptr);

    bool run = true;
    while(run) {
        std::string line;
        std::getline(std::cin, line);

        Commands cmd = extractCommand(line);
        std::vector<std::string> args = extractsArgs(line);

        Command *p_cmd = nullptr;
        switch (cmd)
        {
        case EXIT:
            run = false;
            break;
        
        case LOAD:
            p_cmd = new LoadCmd(args);
            break;

        case DELETE:
            if(args.empty()) {
                std::cout << "invalid command, use:\n delete --all: to delete all the images\n delete id: to delete one image using its id" << std::endl;
            } else if(args[0] == "--all") {
                p_cmd = new DeleteCmd();
            } else {
                try {
                    p_cmd = new DeleteCmd(std::stoi(args[0]));
                } catch(...) {
                    std::cout << args[0] << "is not a valid image id" << std::endl;
                }
            }
            break;

        case SHOW:
            p_cmd = new ShowCmd(args);
            break;

        case SET:
            p_cmd = new SetCmd(args);
            break;

        case MERGE:
            try {
                p_cmd = new MergeCmd(
                    std::stoi(args[0]),
                    std::stoi(args[1]),
                    std::stoi(args[2]),
                    std::stoi(args[3])
                );
            } catch(...) {
                std::cout << "invalid command" << std::endl;
            }
            break;
        
        case UNMERGE:
            try {
                p_cmd = new UnmergeCmd(std::stoi(args[0]));
            } catch(...) {
                std::cout << "invalid command" << std::endl;
            }

        default:
            break;
        }

        if(p_cmd != nullptr) {
            p_cmd->execute(this);
            delete p_cmd;
        } else if(cmd == NONE) {
            std::cout << "unknown command" << std::endl;
        }
    }

    return 0;
}