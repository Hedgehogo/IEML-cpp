#include <gtest/gtest.h>

#include <IEML/parser.hpp>

TEST(parser, Parser_parseLineString) {
	{
		ieml::String str{"> hello"};
		ieml::Parser parser{str};
		auto lineString{parser.parseLineString()};
		auto info{parser.getPosInfo()};
		ASSERT_TRUE(lineString.is_some());
		ASSERT_EQ(lineString.except(), ieml::String{"hello"});
		ASSERT_EQ(info.pos, str.cbegin() + 7);
		ASSERT_EQ(info.mark.line, 0);
		ASSERT_EQ(info.mark.symbol, 7);
	}
	{
		ieml::String str{"> hello\nhello"};
		ieml::Parser parser{str};
		auto lineString{parser.parseLineString()};
		auto info{parser.getPosInfo()};
		ASSERT_TRUE(lineString.is_some());
		ASSERT_EQ(lineString.except(), ieml::String{"hello"});
		ASSERT_EQ(info.pos, str.cbegin() + 7);
		ASSERT_EQ(info.mark.line, 0);
		ASSERT_EQ(info.mark.symbol, 7);
	}
	{
		ieml::String str{">hello"};
		ieml::Parser parser{str};
		auto lineString{parser.parseLineString()};
		auto info{parser.getPosInfo()};
		ASSERT_FALSE(lineString.is_some());
		ASSERT_EQ(info.pos, str.cbegin());
		ASSERT_EQ(info.mark.line, 0);
		ASSERT_EQ(info.mark.symbol, 0);
	}
}