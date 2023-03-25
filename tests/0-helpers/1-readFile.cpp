#include <gtest/gtest.h>
#include <IEML/node/Mark/Mark.hpp>
#include <IEML/helpers/readFile/readFile.hpp>

TEST(helpers, readFile) {
	std::string str{ieml::readFile<char>("../exampleSrc/test.txt")};
}