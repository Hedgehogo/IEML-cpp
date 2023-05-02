#include <gtest/gtest.h>

#include <IEML/parser/helpers/toChar/toChar.hpp>

TEST(parser, helpers_toChar) {
	ASSERT_EQ(ieml::toChar<char32_t>('5'), U'5');
	ASSERT_EQ(ieml::toChar<char16_t>('5'), L'5');
}