#include <gtest/gtest.h>

#include <IEML/parser.hpp>

TEST(parser, Parser_parseNotEscapedString) {
	{
		ieml::String str{
			">>\n"
			"\t\thello"
		};
		ieml::Parser parser{str};
		auto notEscapedString{parser.parseNotEscapedString(2)};
		auto info{parser.getPosInfo()};
		ASSERT_TRUE(notEscapedString.is_some());
		ASSERT_EQ(notEscapedString.except(), ieml::String{"hello"});
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
		auto notEscapedString{parser.parseNotEscapedString(2)};
		auto info{parser.getPosInfo()};
		ASSERT_TRUE(notEscapedString.is_some());
		ASSERT_EQ(notEscapedString.except(), ieml::String{""});
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
		auto notEscapedString{parser.parseNotEscapedString(2)};
		auto info{parser.getPosInfo()};
		ASSERT_TRUE(notEscapedString.is_some());
		ASSERT_EQ(notEscapedString.except(), ieml::String{"hello"});
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
		auto notEscapedString{parser.parseNotEscapedString(2)};
		auto info{parser.getPosInfo()};
		ASSERT_TRUE(notEscapedString.is_some());
		ASSERT_EQ(notEscapedString.except(), ieml::String{"hello\nhello"});
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
		auto notEscapedString{parser.parseNotEscapedString(2)};
		auto info{parser.getPosInfo()};
		ASSERT_TRUE(notEscapedString.is_some());
		ASSERT_EQ(notEscapedString.except(), ieml::String{"hello"});
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
		auto notEscapedString{parser.parseNotEscapedString(2)};
		auto info{parser.getPosInfo()};
		ASSERT_FALSE(notEscapedString.is_some());
		ASSERT_EQ(info.pos, str.cbegin());
		ASSERT_EQ(info.mark.line, 0);
		ASSERT_EQ(info.mark.symbol, 0);
	}
}