#include <gtest/gtest.h>

#include <IEML/node/Mark/Mark.hpp>
#include "IEML/helpers/read_file/read_file.hpp"

TEST(helpers, read_file) {
	std::string str;
	EXPECT_NO_THROW(str = ieml::read_file<char>("../exampleSrc/test.txt"));
	EXPECT_THROW(ieml::read_file<char>("../exampleSrc/other-test.txt"), ieml::FailedOpenFileException);
}