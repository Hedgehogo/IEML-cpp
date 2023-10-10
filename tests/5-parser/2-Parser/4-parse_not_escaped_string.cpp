#include <gtest/gtest.h>

#include <IEML/parser.hpp>

TEST(parser, Parser_parse_not_escaped_string) {
	{
		ieml::String str{
			">>\n"
			"\t\thello"
		};
		ieml::Parser parser{str};
		auto not_escaped_string{parser.parse_not_escaped_string(2)};
		auto info{parser.get_pos_info()};
		ASSERT_TRUE(not_escaped_string.is_some());
		ASSERT_EQ(not_escaped_string.except(), ieml::String{"hello"});
		ASSERT_EQ(info.pos, str.cbegin() + 10);
		ASSERT_EQ(info.mark.line, 1);
		ASSERT_EQ(info.mark.symbol, 7);
	}
	{
		ieml::String str{
			">>\n"
			"\thello"
		};
		ieml::Parser parser{str};
		auto not_escaped_string{parser.parse_not_escaped_string(2)};
		auto info{parser.get_pos_info()};
		ASSERT_TRUE(not_escaped_string.is_some());
		ASSERT_EQ(not_escaped_string.except(), ieml::String{""});
		ASSERT_EQ(info.pos, str.cbegin() + 2);
		ASSERT_EQ(info.mark.line, 0);
		ASSERT_EQ(info.mark.symbol, 2);
	}
	{
		ieml::String str{
			">>\n"
			"\t\thello\n"
			"\thello"
		};
		ieml::Parser parser{str};
		auto not_escaped_string{parser.parse_not_escaped_string(2)};
		auto info{parser.get_pos_info()};
		ASSERT_TRUE(not_escaped_string.is_some());
		ASSERT_EQ(not_escaped_string.except(), ieml::String{"hello"});
		ASSERT_EQ(info.pos, str.cbegin() + 10);
		ASSERT_EQ(info.mark.line, 1);
		ASSERT_EQ(info.mark.symbol, 7);
	}
	{
		ieml::String str{
			">>\n"
			"\t\thello\n"
			"\t\thello\n"
			"\thello"
		};
		ieml::Parser parser{str};
		auto not_escaped_string{parser.parse_not_escaped_string(2)};
		auto info{parser.get_pos_info()};
		ASSERT_TRUE(not_escaped_string.is_some());
		ASSERT_EQ(not_escaped_string.except(), ieml::String{"hello\nhello"});
		ASSERT_EQ(info.pos, str.cbegin() + 18);
		ASSERT_EQ(info.mark.line, 2);
		ASSERT_EQ(info.mark.symbol, 7);
	}
	{
		ieml::String str{
			">> \t# hello\n"
			"\t\thello\n"
			"\thello"
		};
		ieml::Parser parser{str};
		auto not_escaped_string{parser.parse_not_escaped_string(2)};
		auto info{parser.get_pos_info()};
		ASSERT_TRUE(not_escaped_string.is_some());
		ASSERT_EQ(not_escaped_string.except(), ieml::String{"hello"});
		ASSERT_EQ(info.pos, str.cbegin() + 19);
		ASSERT_EQ(info.mark.line, 1);
		ASSERT_EQ(info.mark.symbol, 7);
	}
	{
		ieml::String str{
			">> \t#hello\n"
			"\t\thello\n"
			"\thello"
		};
		ieml::Parser parser{str};
		auto not_escaped_string{parser.parse_not_escaped_string(2)};
		auto info{parser.get_pos_info()};
		ASSERT_FALSE(not_escaped_string.is_some());
		ASSERT_EQ(info.pos, str.cbegin());
		ASSERT_EQ(info.mark.line, 0);
		ASSERT_EQ(info.mark.symbol, 0);
	}
}