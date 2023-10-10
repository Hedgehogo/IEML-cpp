#include <gtest/gtest.h>

#include <IEML/parser.hpp>

TEST(parser, Parser_parse) {
	{
		ieml::String str{
			R"(null)"
		};
		ieml::Parser parser{str};
		auto node{parser.parse()};
		auto info{parser.get_pos_info()};
		ASSERT_TRUE(std::get<6>(node.data_).node_->is_null());
		ASSERT_EQ(info.pos, str.cend());
		ASSERT_EQ(info.mark.line, 0);
		ASSERT_EQ(info.mark.symbol, 4);
	}
	{
		ieml::String str{
			R"( # hello
null)"
		};
		ieml::Parser parser{str};
		auto node{parser.parse()};
		auto info{parser.get_pos_info()};
		ASSERT_TRUE(std::get<6>(node.data_).node_->is_null());
		ASSERT_EQ(info.pos, str.cend());
		ASSERT_EQ(info.mark.line, 1);
		ASSERT_EQ(info.mark.symbol, 4);
	}
	{
		ieml::String str{
			R"(
	-
		null
)"
		};
		ieml::Parser parser{str};
		auto node{parser.parse()};
		auto info{parser.get_pos_info()};
		ASSERT_TRUE(std::get<6>(node.data_).node_->is_list());
		ASSERT_EQ(info.pos, str.cend());
		ASSERT_EQ(info.mark.line, 3);
		ASSERT_EQ(info.mark.symbol, 0);
	}
}