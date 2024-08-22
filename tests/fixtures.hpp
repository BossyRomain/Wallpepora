#ifndef FIXTURES_HPP
#define FIXTURES_HPP

#include <gtest/gtest.h>
#include <vector>

/**
 * This fixture is used to get the list of the files paths of the images used in the tests.
 */
class TestsImagesPaths: public testing::Test {
public:

    // Constructors

    // Destructors

    // Getters
    std::vector<std::string> getValidsImagesPaths() const;

    std::vector<std::string> getInvalidsImagesPaths() const;

    // Setters

    // Instance's methods

protected:

    // Instance's methods
    void SetUp() override;

    void TearDown() override;

private:

    std::vector<std::string> m_validsImagesPaths;

    std::vector<std::string> m_invalidsImagesPaths;
};

#endif