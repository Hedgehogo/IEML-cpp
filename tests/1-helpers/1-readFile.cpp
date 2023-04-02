#include <gtest/gtest.h>

#include <IEML/node/Mark/Mark.hpp>
#include <IEML/helpers/readFile/readFile.hpp>

TEST(helpers, readFile) {
	std::string str;
	EXPECT_NO_THROW(str = ieml::readFile<char>("../exampleSrc/test.txt"));
	EXPECT_THROW(ieml::readFile<char>("../exampleSrc/other-test.txt"), ieml::FailedReadFileException);
}