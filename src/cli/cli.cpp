#include "cli/cli.hpp"
#include "cli/commands/command.hpp"
#include "cli/commands/load_command.hpp"
#include "cli/commands/delete_command.hpp"
#include "cli/commands/show_command.hpp"
#include "cli/commands/set_command.hpp"
#include "cli/commands/merge_command.hpp"
#include "cli/commands/unmerge_command.hpp"
#include "cli/commands/place_command.hpp"
#include "cli/commands/remove_command.hpp"
#include "cli/commands/generate_command.hpp"
#include "cli/commands/export_command.hpp"
#include "cli/commands/fill_command.hpp"
#include "cli/commands/reset_command.hpp"
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
    PLACE,
    REMOVE,
    GENERATE,
    EXPORT,
    FILL,
    RESET,
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
    } else if(cmd == "place") {
        return PLACE;
    } else if(cmd == "remove") {
        return REMOVE;
    } else if(cmd == "generate") {
        return GENERATE;
    } else if(cmd == "export") {
        return EXPORT;
    } else if(cmd == "fill") {
        return FILL;
    } else if(cmd == "reset") {
        return RESET;
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
CLI::CLI(): m_imagesController(nullptr), m_gridController(nullptr), m_wallpapersController(nullptr), m_workspaceController(nullptr) {}

// Destructor
CLI::~CLI() {}

// Getters
ImagesController* CLI::getImagesController() const {
    return m_imagesController;
}

GridController* CLI::getGridController() const {
    return m_gridController;
}

WallpapersController* CLI::getWallpapersController() const {
    return m_wallpapersController;
}

WorkspaceController* CLI::getWorkspaceController() const {
    return m_workspaceController;
}

// Setters
void CLI::setImagesController(ImagesController *p_imagesController) {
    m_imagesController = p_imagesController;
}

void CLI::setGridController(GridController *p_gridController) {
    m_gridController = p_gridController;
}

void CLI::setWallpapersController(WallpapersController *p_wallpapersController) {
    m_wallpapersController = p_wallpapersController;
}

void CLI::setWorkspaceController(WorkspaceController *p_workspaceController) {
    m_workspaceController = p_workspaceController;
}

// Instance's methods
int CLI::run() {
    assert(m_imagesController != nullptr);
    assert(m_gridController != nullptr);
    assert(m_wallpapersController != nullptr);
    assert(m_workspaceController != nullptr);

    bool run = true;
    while(run) {
        std::string line;
        std::getline(std::cin, line);

        Commands cmd = extractCommand(line);
        std::vector<std::string> args = extractsArgs(line);

        Command *p_cmd = nullptr;
        try {
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
                    std::cout << "invalid command" << std::endl;
                } else if(args[0] == "--all") {
                    p_cmd = new DeleteCmd();
                } else {
                    try {
                        p_cmd = new DeleteCmd(std::stoi(args[0]));
                    } catch(...) {
                        std::cout << args[0] << "is not a valid image id" << std::endl;
                        throw std::exception();
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
                p_cmd = new MergeCmd(
                    std::stoi(args[0]),
                    std::stoi(args[1]),
                    std::stoi(args[2]),
                    std::stoi(args[3])
                    );
                break;
            
            case UNMERGE:
                p_cmd = new UnmergeCmd(std::stoi(args[0]));
                break;

            case PLACE:
                if(args.size() == 2) {
                    p_cmd = new PlaceCmd(std::stoi(args[0]), std::stoi(args[1]));
                } else if(args.size() == 3) {
                    p_cmd = new PlaceCmd(std::stoi(args[0]), std::stoi(args[1]), std::stoi(args[2]));
                } else {
                    throw std::exception();
                }
                break;

            case REMOVE:
                if(args.size() == 1) {
                    if(args[0] == "--all") {
                        p_cmd = new RemoveCmd();
                    } else {
                        p_cmd = new RemoveCmd(std::stoi(args[0]));
                    }
                } else if(args.size() == 2) {
                    p_cmd = new RemoveCmd(std::stoi(args[0]), std::stoi(args[1]));
                } else {
                    throw std::exception();
                }
                break;

            case GENERATE:
                p_cmd = new GenerateCmd();
                break;

            case EXPORT:
                if(args.size() == 2) {
                    p_cmd = new ExportCmd(std::stoi(args[0]), args[1]);
                } else {
                    throw std::exception();
                }
                break;

            case FILL:
                if(args.size() == 0) {
                    p_cmd = new FillCmd();
                } else if(args.size() == 1 && args[0] == "--hard") {
                    p_cmd = new FillCmd(true);
                } else {
                    throw std::exception();
                }
                break;

            case RESET:
                p_cmd = new ResetCmd();
                break;

            default:
                break;
            }

            if(p_cmd != nullptr) {
                p_cmd->execute(this);
                delete p_cmd;
            } else if(cmd == NONE) {
                std::cout << "unknown command" << std::endl;
            }
        } catch(...) {
            std::cout << "invalid command" << std::endl;
        }
    }

    return 0;
}