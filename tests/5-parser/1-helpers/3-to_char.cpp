#include <gtest/gtest.h>

#include <IEML/parser/helpers/to_char/to_char.hpp>

TEST(parser, helpers_to_char) {
	ASSERT_EQ(ieml::to_char<char32_t>('5'), U'5');
	ASSERT_EQ(ieml::to_char<char16_t>('5'), L'5');
}