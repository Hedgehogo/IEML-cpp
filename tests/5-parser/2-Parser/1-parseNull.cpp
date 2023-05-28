#include <gtest/gtest.h>

#include <IEML/parser.hpp>

TEST(parser, Parser_parseNull) {
	{
		ieml::String str{"null"};
		ieml::Parser parser{str};
		auto null{parser.parseNull()};
		auto info{parser.getPosInfo()};
		ASSERT_TRUE(null.is_some());
		ASSERT_EQ(info.pos, str.cend());
		ASSERT_EQ(info.mark.line, 0);
		ASSERT_EQ(info.mark.symbol, 4);
	}
	{
		ieml::String str{"null "};
		ieml::Parser parser{str};
		auto null{parser.parseNull()};
		auto info{parser.getPosInfo()};
		ASSERT_TRUE(null.is_some());
		ASSERT_EQ(info.pos, str.cend());
		ASSERT_EQ(info.mark.line, 0);
		ASSERT_EQ(info.mark.symbol, 5);
	}
	{
		ieml::String str{"null# is null"};
		ieml::Parser parser{str};
		auto null{parser.parseNull()};
		auto info{parser.getPosInfo()};
		ASSERT_TRUE(null.is_some());
		ASSERT_EQ(info.pos, str.cbegin() + 4);
		ASSERT_EQ(info.mark.line, 0);
		ASSERT_EQ(info.mark.symbol, 4);
	}
	{
		ieml::String str{"null # is null"};
		ieml::Parser parser{str};
		auto null{parser.parseNull()};
		auto info{parser.getPosInfo()};
		ASSERT_TRUE(null.is_some());
		ASSERT_EQ(info.pos, str.cbegin() + 5);
		ASSERT_EQ(info.mark.line, 0);
		ASSERT_EQ(info.mark.symbol, 5);
	}
	{
		ieml::String str{" null"};
		ieml::Parser parser{str};
		auto null{parser.parseNull()};
		auto info{parser.getPosInfo()};
		ASSERT_FALSE(null.is_some());
		ASSERT_EQ(info.pos, str.cbegin());
		ASSERT_EQ(info.mark.line, 0);
		ASSERT_EQ(info.mark.symbol, 0);
	}
}