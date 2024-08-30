#ifndef CLI_UTILS_HPP
#define CLI_UTILS_HPP

#include <string>

/**
 * Asks the user to confirm an action.
 * The user must answer on the standard input using :
 * - y or yes for confirming.
 * - anything else to cancel.
 * 
 * @param msg the message of confirmation to print on the standard output.
 * @return true if the user confirms the action, else false.
 */
bool confirmAction(const std::string& msg);

#endif