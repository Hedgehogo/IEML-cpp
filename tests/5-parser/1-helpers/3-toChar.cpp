#include <gtest/gtest.h>

#include <IEML/parser/helpers/toChar/toChar.hpp>

TEST(parser, helpers_toChar) {
	ASSERT_EQ(ieml::toChar(U'5'), '5');
	ASSERT_EQ(ieml::toChar(L'5'), '5');
}