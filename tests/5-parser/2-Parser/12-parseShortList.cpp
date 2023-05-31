#include <gtest/gtest.h>

#include <IEML/parser.hpp>

TEST(parser, Parser_parseShortList) {
	{
		ieml::String str{"[]"};
		ieml::Parser parser{str};
		auto shortList{parser.parseShortList()};
		auto info{parser.getPosInfo()};
		ASSERT_TRUE(shortList.is_some());
		ASSERT_EQ(shortList.except().size(), 0);
		ASSERT_EQ(info.pos, str.begin() + 2);
		ASSERT_EQ(info.mark.line, 0);
		ASSERT_EQ(info.mark.symbol, 2);
	}
	{
		ieml::String str{"[]# hello"};
		ieml::Parser parser{str};
		auto shortList{parser.parseShortList()};
		auto info{parser.getPosInfo()};
		ASSERT_TRUE(shortList.is_some());
		ASSERT_EQ(shortList.except().size(), 0);
		ASSERT_EQ(info.pos, str.begin() + 9);
		ASSERT_EQ(info.mark.line, 0);
		ASSERT_EQ(info.mark.symbol, 9);
	}
	{
		ieml::String str{"[null]"};
		ieml::Parser parser{str};
		auto shortList{parser.parseShortList()};
		auto info{parser.getPosInfo()};
		ASSERT_TRUE(shortList.is_some());
		ASSERT_EQ(shortList.except().size(), 1);
		ASSERT_TRUE(shortList.except().at(0).isNull());
		ASSERT_EQ(info.pos, str.begin() + 6);
		ASSERT_EQ(info.mark.line, 0);
		ASSERT_EQ(info.mark.symbol, 6);
	}
	{
		ieml::String str{"[null, null]"};
		ieml::Parser parser{str};
		auto shortList{parser.parseShortList()};
		auto info{parser.getPosInfo()};
		ASSERT_TRUE(shortList.is_some());
		ASSERT_EQ(shortList.except().size(), 2);
		ASSERT_TRUE(shortList.except().at(0).isNull());
		ASSERT_TRUE(shortList.except().at(1).isNull());
		ASSERT_EQ(info.pos, str.begin() + 12);
		ASSERT_EQ(info.mark.line, 0);
		ASSERT_EQ(info.mark.symbol, 12);
	}
	{
		ieml::String str{"[hello]"};
		ieml::Parser parser{str};
		auto shortList{parser.parseShortList()};
		auto info{parser.getPosInfo()};
		ASSERT_TRUE(shortList.is_some());
		ASSERT_EQ(shortList.except().size(), 1);
		ASSERT_TRUE(shortList.except().at(0).isRaw());
		ASSERT_EQ(info.pos, str.begin() + 7);
		ASSERT_EQ(info.mark.line, 0);
		ASSERT_EQ(info.mark.symbol, 7);
	}
	{
		ieml::String str{R"(["hello"])"};
		ieml::Parser parser{str};
		auto shortList{parser.parseShortList()};
		auto info{parser.getPosInfo()};
		ASSERT_TRUE(shortList.is_some());
		ASSERT_EQ(shortList.except().size(), 1);
		ASSERT_TRUE(shortList.except().at(0).isString());
		ASSERT_EQ(info.pos, str.begin() + 9);
		ASSERT_EQ(info.mark.line, 0);
		ASSERT_EQ(info.mark.symbol, 9);
	}
	{
		ieml::String str{"[[null]]"};
		ieml::Parser parser{str};
		auto shortList{parser.parseShortList()};
		auto info{parser.getPosInfo()};
		ASSERT_TRUE(shortList.is_some());
		ASSERT_EQ(shortList.except().size(), 1);
		ASSERT_TRUE(shortList.except().at(0).isList());
		ASSERT_EQ(info.pos, str.begin() + 8);
		ASSERT_EQ(info.mark.line, 0);
		ASSERT_EQ(info.mark.symbol, 8);
	}
	{
		ieml::String str{"[# ]"};
		ieml::Parser parser{str};
		EXPECT_THROW(parser.parseShortList(), ieml::FailedParseException);
	}
	{
		ieml::String str{"[null"};
		ieml::Parser parser{str};
		EXPECT_THROW(parser.parseShortList(), ieml::FailedParseException);
	}
}