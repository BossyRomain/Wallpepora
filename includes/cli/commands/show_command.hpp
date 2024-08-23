#ifndef SHOW_COMMAND_HPP
#define SHOW_COMMAND_HPP

#include "cli/commands/command.hpp"

/**
 * This command can show informations about the application on the standard output.
 */
class ShowCmd: public Command {
public:

    // Constructors
    ShowCmd(std::vector<std::string> args);

    // Destructor

    // Getters

    // Setters

    // Instance's methods
    void execute(CLI *p_cli) override;

private:

    // Instance's methods
    void showImages(CLI *p_cli);

    void showTiles(CLI *p_cli);

    // Attributes
    std::vector<std::string> m_args;
};

#endif