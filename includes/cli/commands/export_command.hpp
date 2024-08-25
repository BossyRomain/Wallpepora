#ifndef EXPORT_COMMAND_HPP
#define EXPORT_COMMAND_HPP

#include "cli/commands/command.hpp"

class ExportCmd: public Command {
public:

    // Constructors
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