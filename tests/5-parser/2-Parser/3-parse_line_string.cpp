#include <gtest/gtest.h>

#include <IEML/parser.hpp>

TEST(parser, Parser_parse_line_string) {
	{
		ieml::String str{"> hello"};
		ieml::Parser parser{str};
		auto line_string{parser.parse_line_string()};
		auto info{parser.get_pos_info()};
		ASSERT_TRUE(line_string.is_some());
		ASSERT_EQ(line_string.except(), ieml::String{"hello"});
		ASSERT_EQ(info.pos, str.cbegin() + 7);
		ASSERT_EQ(info.mark.line, 0);
		ASSERT_EQ(info.mark.symbol, 7);
	}
	{
		ieml::String str{"> hello\nhello"};
		ieml::Parser parser{str};
		auto line_string{parser.parse_line_string()};
		auto info{parser.get_pos_info()};
		ASSERT_TRUE(line_string.is_some());
		ASSERT_EQ(line_string.except(), ieml::String{"hello"});
		ASSERT_EQ(info.pos, str.cbegin() + 7);
		ASSERT_EQ(info.mark.line, 0);
		ASSERT_EQ(info.mark.symbol, 7);
	}
	{
		ieml::String str{">hello"};
		ieml::Parser parser{str};
		auto line_string{parser.parse_line_string()};
		auto info{parser.get_pos_info()};
		ASSERT_FALSE(line_string.is_some());
		ASSERT_EQ(info.pos, str.cbegin());
		ASSERT_EQ(info.mark.line, 0);
		ASSERT_EQ(info.mark.symbol, 0);
	}
}