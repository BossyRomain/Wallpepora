#ifndef SET_COMMAND_HPP
#define SET_COMMAND_HPP

#include "cli/commands/command.hpp"
#include <vector>

/**
 * This command updates the grid's dimensions which means :
 * - the number of rows
 * - the number of columns
 * - the cells' size (in pixels)
 * 
 * This command recognizes the following options to update the number of rows :
 * - -r value
 * - --rows=value
 * 
 * This command recognizes the following options to update the number of columns :
 * - -c value
 * - --cols=value
 * 
 * This command recognizes the following options to update the cells' size :
 * - -s value
 * - --size=value
 * 
 * For each dimension, a message is shown if success, else an error message is shown. 
 */
class SetCmd: public Command {
public:

    // Constructors
    /**
     * Constructs a set command with its arguments.
     * 
     * @param args - the arguments of the command.
     */
    SetCmd(std::vector<std::string> args);

    // Destructor

    // Getters

    // Setters

    // Instance's method
    void execute(CLI *p_cli) override;

private:

    // Instance's methods
    void updateRows(GridController *p_gridController, int rows) const;

    void updateCols(GridController *p_gridController, int cols) const;

    void updateSize(GridController *p_gridController, int size) const;

    // Attributes
    std::vector<std::string> m_args;
};

#endif