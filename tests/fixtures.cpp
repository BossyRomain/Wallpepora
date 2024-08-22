#include "fixtures.hpp"
#include <filesystem>
namespace fs = std::filesystem;

// Constructors

// Destructors

// Getters
std::vector<std::string> TestsImagesPaths::getValidsImagesPaths() const {
    return m_validsImagesPaths;
}

std::vector<std::string> TestsImagesPaths::getInvalidsImagesPaths() const {
    return m_invalidsImagesPaths;
}

// Setters

// Instance's methods
void TestsImagesPaths::SetUp() {
    for(auto& file: fs::directory_iterator("./tests_res/images/valids/")) {
        m_validsImagesPaths.push_back(file.path());
    }

    for(auto& file: fs::directory_iterator("./tests_res/images/invalids/")) {
        m_invalidsImagesPaths.push_back(file.path());
        
        if(file.path().string().find("no_permissions") != std::string::npos) {
            fs::permissions(file.path(), fs::perms::none);
        }
    }
}

void TestsImagesPaths::TearDown() {
    for(auto& file: fs::directory_iterator("./tests_res/images/invalids/")) {        
        if(file.path().string().find("no_permissions") != std::string::npos) {
            fs::permissions(file.path(), fs::perms::all);
        }
    }
}