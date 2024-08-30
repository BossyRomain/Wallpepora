#include "cli/cli_utils.hpp"
#include <iostream>

bool confirmAction(const std::string& msg) {
    std::cout << msg << std::endl;
    std::string answer;
    std::getline(std::cin, answer);

    return answer == "y" || answer == "yes";
}