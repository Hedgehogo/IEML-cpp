#include <gtest/gtest.h>

#include <IEML/parser.hpp>

TEST(parser, Parser_parse_short_list) {
	{
		ieml::String str{"[]"};
		ieml::Parser parser{str};
		auto short_list{parser.parse_short_list()};
		auto info{parser.get_pos_info()};
		ASSERT_TRUE(short_list.is_some());
		ASSERT_EQ(short_list.except().size(), 0);
		ASSERT_EQ(info.pos, str.begin() + 2);
		ASSERT_EQ(info.mark.line, 0);
		ASSERT_EQ(info.mark.symbol, 2);
	}
	{
		ieml::String str{"[]# hello"};
		ieml::Parser parser{str};
		auto short_list{parser.parse_short_list()};
		auto info{parser.get_pos_info()};
		ASSERT_TRUE(short_list.is_some());
		ASSERT_EQ(short_list.except().size(), 0);
		ASSERT_EQ(info.pos, str.begin() + 9);
		ASSERT_EQ(info.mark.line, 0);
		ASSERT_EQ(info.mark.symbol, 9);
	}
	{
		ieml::String str{"[null]"};
		ieml::Parser parser{str};
		auto short_list{parser.parse_short_list()};
		auto info{parser.get_pos_info()};
		ASSERT_TRUE(short_list.is_some());
		ASSERT_EQ(short_list.except().size(), 1);
		ASSERT_EQ(short_list.except().at(0).get_type(), ieml::NodeType::Null);
		ASSERT_EQ(info.pos, str.begin() + 6);
		ASSERT_EQ(info.mark.line, 0);
		ASSERT_EQ(info.mark.symbol, 6);
	}
	{
		ieml::String str{"[null, null]"};
		ieml::Parser parser{str};
		auto short_list{parser.parse_short_list()};
		auto info{parser.get_pos_info()};
		ASSERT_TRUE(short_list.is_some());
		ASSERT_EQ(short_list.except().size(), 2);
		ASSERT_EQ(short_list.except().at(0).get_type(), ieml::NodeType::Null);
		ASSERT_EQ(short_list.except().at(0).get_type(), ieml::NodeType::Null);
		ASSERT_EQ(info.pos, str.begin() + 12);
		ASSERT_EQ(info.mark.line, 0);
		ASSERT_EQ(info.mark.symbol, 12);
	}
	{
		ieml::String str{"[hello]"};
		ieml::Parser parser{str};
		auto short_list{parser.parse_short_list()};
		auto info{parser.get_pos_info()};
		ASSERT_TRUE(short_list.is_some());
		ASSERT_EQ(short_list.except().size(), 1);
		ASSERT_EQ(short_list.except().at(0).get_type(), ieml::NodeType::Raw);
		ASSERT_EQ(info.pos, str.begin() + 7);
		ASSERT_EQ(info.mark.line, 0);
		ASSERT_EQ(info.mark.symbol, 7);
	}
	{
		ieml::String str{R"(["hello"])"};
		ieml::Parser parser{str};
		auto short_list{parser.parse_short_list()};
		auto info{parser.get_pos_info()};
		ASSERT_TRUE(short_list.is_some());
		ASSERT_EQ(short_list.except().size(), 1);
		ASSERT_EQ(short_list.except().at(0).get_type(), ieml::NodeType::String);
		ASSERT_EQ(info.pos, str.begin() + 9);
		ASSERT_EQ(info.mark.line, 0);
		ASSERT_EQ(info.mark.symbol, 9);
	}
	{
		ieml::String str{R"([*anchor])"};
		ieml::Parser parser{str};
		auto short_list{parser.parse_short_list()};
		auto info{parser.get_pos_info()};
		ASSERT_TRUE(short_list.is_some());
		ASSERT_EQ(short_list.except().size(), 1);
		ASSERT_EQ(short_list.except().at(0).get_type(), ieml::NodeType::GetAnchor);
		ASSERT_EQ(short_list.except().at(0).get_get_anchor_name().except(), "anchor");
		ASSERT_EQ(info.pos, str.begin() + 9);
		ASSERT_EQ(info.mark.line, 0);
		ASSERT_EQ(info.mark.symbol, 9);
	}
	{
		ieml::String str{"[[null]]"};
		ieml::Parser parser{str};
		auto short_list{parser.parse_short_list()};
		auto info{parser.get_pos_info()};
		ASSERT_TRUE(short_list.is_some());
		ASSERT_EQ(short_list.except().size(), 1);
		ASSERT_TRUE(short_list.except().at(0).is_list());
		ASSERT_EQ(info.pos, str.begin() + 8);
		ASSERT_EQ(info.mark.line, 0);
		ASSERT_EQ(info.mark.symbol, 8);
	}
	{
		ieml::String str{"[# ]"};
		ieml::Parser parser{str};
		EXPECT_THROW(parser.parse_short_list(), ieml::FailedParseException);
	}
	{
		ieml::String str{"[null"};
		ieml::Parser parser{str};
		EXPECT_THROW(parser.parse_short_list(), ieml::FailedParseException);
	}
}