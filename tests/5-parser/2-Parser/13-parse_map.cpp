#include <gtest/gtest.h>

#include <IEML/parser.hpp>

TEST(parser, Parser_parse_map) {
	{
		ieml::String str{R"(first: null)"};
		ieml::Parser parser{str};
		auto map{parser.parse_map(2)};
		auto info{parser.get_pos_info()};
		ASSERT_TRUE(map.is_some());
		ASSERT_EQ(map.except().size(), 1);
		ASSERT_TRUE(map.except().at(ieml::String{"first"}).is_null());
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
		auto map{parser.parse_map(2)};
		auto info{parser.get_pos_info()};
		ASSERT_TRUE(map.is_some());
		ASSERT_EQ(map.except().size(), 1);
		ASSERT_TRUE(map.except().at(ieml::String{"first"}).is_null());
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
		EXPECT_THROW(parser.parse_map(2), ieml::FailedParseException);
	}
	{
		ieml::String str{
			R"(first: null
		second: null)"
		};
		ieml::Parser parser{str};
		auto map{parser.parse_map(2)};
		auto info{parser.get_pos_info()};
		ASSERT_TRUE(map.is_some());
		ASSERT_EQ(map.except().size(), 2);
		ASSERT_TRUE(map.except().at(ieml::String{"first"}).is_null());
		ASSERT_TRUE(map.except().at(ieml::String{"second"}).is_null());
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
		auto map{parser.parse_map(2)};
		auto info{parser.get_pos_info()};
		ASSERT_TRUE(map.is_some());
		ASSERT_EQ(map.except().size(), 1);
		ASSERT_TRUE(map.except().at(ieml::String{"first"}).is_null());
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
		EXPECT_THROW(parser.parse_map(2), ieml::FailedParseException);
	}
	{
		ieml::String str{
			R"(first: null
 	# hello
		second: null)"
		};
		ieml::Parser parser{str};
		auto map{parser.parse_map(2)};
		auto info{parser.get_pos_info()};
		ASSERT_TRUE(map.is_some());
		ASSERT_EQ(map.except().size(), 2);
		ASSERT_TRUE(map.except().at(ieml::String{"first"}).is_null());
		ASSERT_TRUE(map.except().at(ieml::String{"second"}).is_null());
		ASSERT_EQ(info.pos, str.cbegin() + 36);
		ASSERT_EQ(info.mark.line, 2);
		ASSERT_EQ(info.mark.symbol, 14);
	}
	{
		ieml::String str{R"(first:null)"};
		ieml::Parser parser{str};
		auto map{parser.parse_map(2)};
		auto info{parser.get_pos_info()};
		ASSERT_FALSE(map.is_some());
		ASSERT_EQ(info.pos, str.cbegin());
		ASSERT_EQ(info.mark.line, 0);
		ASSERT_EQ(info.mark.symbol, 0);
	}
}