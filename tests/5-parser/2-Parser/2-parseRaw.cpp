#include <gtest/gtest.h>

#include <IEML/node/Node/Node.hpp>

TEST(parser, Parser_parseRaw) {
	{
		ieml::String str{"hello"};
		ieml::Parser parser{str};
		auto null{parser.parseRaw()};
		auto info{parser.getPosInfo()};
		ASSERT_TRUE(null.is_some());
		ASSERT_EQ(null.except().str, ieml::String{"hello"});
		ASSERT_EQ(info.pos, str.cbegin() + 5);
		ASSERT_EQ(info.mark.line, 0);
		ASSERT_EQ(info.mark.symbol, 5);
	}
	{
		ieml::String str{"hello\n"};
		ieml::Parser parser{str};
		auto null{parser.parseRaw()};
		auto info{parser.getPosInfo()};
		ASSERT_TRUE(null.is_some());
		ASSERT_EQ(null.except().str, ieml::String{"hello"});
		ASSERT_EQ(info.pos, str.cbegin() + 5);
		ASSERT_EQ(info.mark.line, 0);
		ASSERT_EQ(info.mark.symbol, 5);
	}
	{
		ieml::String str{"< \n"};
		ieml::Parser parser{str};
		auto null{parser.parseRaw()};
		auto info{parser.getPosInfo()};
		ASSERT_FALSE(null.is_some());
		ASSERT_EQ(info.pos, str.cbegin());
		ASSERT_EQ(info.mark.line, 0);
		ASSERT_EQ(info.mark.symbol, 0);
	}
}