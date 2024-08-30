#ifndef EXPORT_COMMAND_HPP
#define EXPORT_COMMAND_HPP

#include "cli/commands/command.hpp"

/**
 * This command exports a wallpaper in a file using the wallpaper's and a file path.
 */
class ExportCmd: public Command {
public:

    // Constructors
    /**
     * Constructs an export command to export a wallpaper with the specified id in the specified file.
     */
    ExportCmd(int id, const std::string& filePath);

    // Destructor

    // Getters

    // Setters

    // Instance's methods
    void execute(CLI *p_cli) override;

private:

    int m_id;

    std::string m_filePath;
};

#endif