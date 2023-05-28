#include <gtest/gtest.h>

#include <IEML/parser.hpp>

TEST(parser, Parser_parseMap) {
	{
		ieml::String str{R"(first: null)"};
		ieml::Parser parser{str};
		auto map{parser.parseMap(2)};
		auto info{parser.getPosInfo()};
		ASSERT_TRUE(map.is_some());
		ASSERT_EQ(map.except().size(), 1);
		ASSERT_TRUE(map.except().at(ieml::String{"first"}).isNull());
		ASSERT_EQ(info.pos, str.cbegin() + 11);
		ASSERT_EQ(info.mark.line, 0);
		ASSERT_EQ(info.mark.symbol, 11);
	}
	{
		ieml::String str{
			R"(first:
			null)"
		};
		ieml::Parser parser{str};
		auto map{parser.parseMap(2)};
		auto info{parser.getPosInfo()};
		ASSERT_TRUE(map.is_some());
		ASSERT_EQ(map.except().size(), 1);
		ASSERT_TRUE(map.except().at(ieml::String{"first"}).isNull());
		ASSERT_EQ(info.pos, str.cbegin() + 14);
		ASSERT_EQ(info.mark.line, 1);
		ASSERT_EQ(info.mark.symbol, 7);
	}
	{
		ieml::String str{
			R"(first:
		null)"
		};
		ieml::Parser parser{str};
		EXPECT_THROW(parser.parseMap(2), ieml::FailedParseException);
	}
	{
		ieml::String str{
			R"(first: null
		second: null)"
		};
		ieml::Parser parser{str};
		auto map{parser.parseMap(2)};
		auto info{parser.getPosInfo()};
		ASSERT_TRUE(map.is_some());
		ASSERT_EQ(map.except().size(), 2);
		ASSERT_TRUE(map.except().at(ieml::String{"first"}).isNull());
		ASSERT_TRUE(map.except().at(ieml::String{"second"}).isNull());
		ASSERT_EQ(info.pos, str.cbegin() + 26);
		ASSERT_EQ(info.mark.line, 1);
		ASSERT_EQ(info.mark.symbol, 14);
	}
	{
		ieml::String str{
			R"(first: null
	second: null)"
		};
		ieml::Parser parser{str};
		auto map{parser.parseMap(2)};
		auto info{parser.getPosInfo()};
		ASSERT_TRUE(map.is_some());
		ASSERT_EQ(map.except().size(), 1);
		ASSERT_TRUE(map.except().at(ieml::String{"first"}).isNull());
		ASSERT_EQ(info.pos, str.cbegin() + 11);
		ASSERT_EQ(info.mark.line, 0);
		ASSERT_EQ(info.mark.symbol, 11);
	}
	{
		ieml::String str{
			R"(first: null
			second: null)"
		};
		ieml::Parser parser{str};
		EXPECT_THROW(parser.parseMap(2), ieml::FailedParseException);
	}
	{
		ieml::String str{
			R"(first: null
 	# hello
		second: null)"
		};
		ieml::Parser parser{str};
		auto map{parser.parseMap(2)};
		auto info{parser.getPosInfo()};
		ASSERT_TRUE(map.is_some());
		ASSERT_EQ(map.except().size(), 2);
		ASSERT_TRUE(map.except().at(ieml::String{"first"}).isNull());
		ASSERT_TRUE(map.except().at(ieml::String{"second"}).isNull());
		ASSERT_EQ(info.pos, str.cbegin() + 36);
		ASSERT_EQ(info.mark.line, 2);
		ASSERT_EQ(info.mark.symbol, 14);
	}
	{
		ieml::String str{R"(first:null)"};
		ieml::Parser parser{str};
		auto map{parser.parseMap(2)};
		auto info{parser.getPosInfo()};
		ASSERT_FALSE(map.is_some());
		ASSERT_EQ(info.pos, str.cbegin());
		ASSERT_EQ(info.mark.line, 0);
		ASSERT_EQ(info.mark.symbol, 0);
	}
}