#include <gtest/gtest.h>

#include <IEML/parser.hpp>

TEST(parser, Parser_parse_tag) {
	{
		ieml::String str{"= Tag: null"};
		ieml::Parser parser{str};
		auto tag{parser.parse_tag(2)};
		auto info{parser.get_pos_info()};
		ASSERT_TRUE(tag.is_some());
		ASSERT_EQ(tag.except().tag_, ieml::String{"Tag"});
		ASSERT_TRUE(tag.except().node_->is_null());
		ASSERT_EQ(info.pos, str.cbegin() + 11);
		ASSERT_EQ(info.mark.line, 0);
		ASSERT_EQ(info.mark.symbol, 11);
	}
	{
		ieml::String str{
			R"(= Tag:
		null)"
		};
		ieml::Parser parser{str};
		auto tag{parser.parse_tag(2)};
		auto info{parser.get_pos_info()};
		ASSERT_TRUE(tag.is_some());
		ASSERT_EQ(tag.except().tag_, ieml::String{"Tag"});
		ASSERT_TRUE(tag.except().node_->is_null());
		ASSERT_EQ(info.pos, str.cbegin() + 13);
		ASSERT_EQ(info.mark.line, 1);
		ASSERT_EQ(info.mark.symbol, 6);
	}
	{
		ieml::String str{"= \n: null"};
		ieml::Parser parser{str};
		auto tag{parser.parse_tag(2)};
		auto info{parser.get_pos_info()};
		ASSERT_FALSE(tag.is_some());
		ASSERT_EQ(info.pos, str.cbegin());
		ASSERT_EQ(info.mark.line, 0);
		ASSERT_EQ(info.mark.symbol, 0);
	}
}