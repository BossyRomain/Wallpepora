#ifndef CLI_HPP
#define CLI_HPP

#include "controllers/images_controller.hpp"
#include "cli/commands/command.hpp"

class Command;

/**
 * The class used for the CLI. It reads user commands on the standard input, process them and executes them.
 */
class CLI {
public:

    // Constructors
    CLI();

    // Destructor
    ~CLI();

    // Getters
    ImagesController* getImagesController() const;

    // Setters
    void setImagesController(ImagesController *p_imagesController);

    // Instance's methods
    /**
     * Reads commands on the standard input and process them.
     * Stops when the command exit is entered or when an error happens.
     * 
     * @returns 0 if the exit command exit is entered, else a error code.
     */
    int run();

private:

    ImagesController *m_imagesController;
};

#endif