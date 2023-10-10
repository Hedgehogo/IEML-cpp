#include <gtest/gtest.h>

#include <IEML/parser.hpp>

TEST(parser, Parser_parse_list) {
	{
		ieml::String str{R"(- null)"};
		ieml::Parser parser{str};
		auto list{parser.parse_list(2)};
		auto info{parser.get_pos_info()};
		ASSERT_TRUE(list.is_some());
		ASSERT_EQ(list.except().size(), 1);
		ASSERT_TRUE(list.except().at(0).is_null());
		ASSERT_EQ(info.pos, str.cbegin() + 6);
		ASSERT_EQ(info.mark.line, 0);
		ASSERT_EQ(info.mark.symbol, 6);
	}
	{
		ieml::String str{
			R"(-
			null)"
		};
		ieml::Parser parser{str};
		auto list{parser.parse_list(2)};
		auto info{parser.get_pos_info()};
		ASSERT_TRUE(list.is_some());
		ASSERT_EQ(list.except().size(), 1);
		ASSERT_TRUE(list.except().at(0).is_null());
		ASSERT_EQ(info.pos, str.cbegin() + 9);
		ASSERT_EQ(info.mark.line, 1);
		ASSERT_EQ(info.mark.symbol, 7);
	}
	{
		ieml::String str{
			R"(-
		null)"
		};
		ieml::Parser parser{str};
		EXPECT_THROW(parser.parse_list(2), ieml::FailedParseException);
	}
	{
		ieml::String str{
			R"(- null
		- null)"
		};
		ieml::Parser parser{str};
		auto list{parser.parse_list(2)};
		auto info{parser.get_pos_info()};
		ASSERT_TRUE(list.is_some());
		ASSERT_EQ(list.except().size(), 2);
		ASSERT_TRUE(list.except().at(0).is_null());
		ASSERT_TRUE(list.except().at(1).is_null());
		ASSERT_EQ(info.pos, str.cbegin() + 15);
		ASSERT_EQ(info.mark.line, 1);
		ASSERT_EQ(info.mark.symbol, 8);
	}
	{
		ieml::String str{
			R"(- null
	- null)"
		};
		ieml::Parser parser{str};
		auto list{parser.parse_list(2)};
		auto info{parser.get_pos_info()};
		ASSERT_TRUE(list.is_some());
		ASSERT_EQ(list.except().size(), 1);
		ASSERT_TRUE(list.except().at(0).is_null());
		ASSERT_EQ(info.pos, str.cbegin() + 6);
		ASSERT_EQ(info.mark.line, 0);
		ASSERT_EQ(info.mark.symbol, 6);
	}
	{
		ieml::String str{
			R"(- null
			- null)"
		};
		ieml::Parser parser{str};
		EXPECT_THROW(parser.parse_list(2), ieml::FailedParseException);
	}
	{
		ieml::String str{
			R"(- null
 	# hello
		- null)"
		};
		ieml::Parser parser{str};
		auto list{parser.parse_list(2)};
		auto info{parser.get_pos_info()};
		ASSERT_TRUE(list.is_some());
		ASSERT_EQ(list.except().size(), 2);
		ASSERT_TRUE(list.except().at(0).is_null());
		ASSERT_TRUE(list.except().at(1).is_null());
		ASSERT_EQ(info.pos, str.cbegin() + 25);
		ASSERT_EQ(info.mark.line, 2);
		ASSERT_EQ(info.mark.symbol, 8);
	}
	{
		ieml::String str{R"(-null)"};
		ieml::Parser parser{str};
		auto list{parser.parse_list(2)};
		auto info{parser.get_pos_info()};
		ASSERT_FALSE(list.is_some());
		ASSERT_EQ(info.pos, str.cbegin());
		ASSERT_EQ(info.mark.line, 0);
		ASSERT_EQ(info.mark.symbol, 0);
	}
}