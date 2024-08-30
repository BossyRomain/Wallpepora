
#ifndef GENERATE_COMMAND_HPP
#define GENERATE_COMMAND_HPP

#include "cli/commands/command.hpp"

/**
 * This command generates a new wallpaper if possible.
 * 
 * If the generation success, the id of the new wallpaper is shown, else an error message is shown.
 */
class GenerateCmd: public Command {
public:

    // Constructors

    // Destructor

    // Getters

    // Setters

    // Instance's methods
    void execute(CLI *p_cli) override;
    
private:
};

#endif