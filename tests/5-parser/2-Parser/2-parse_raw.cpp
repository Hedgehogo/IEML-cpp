#include <gtest/gtest.h>

#include <IEML/parser.hpp>

TEST(parser, Parser_parse_raw) {
	{
		ieml::String str{"hello"};
		ieml::Parser parser{str};
		auto raw{parser.parse_raw()};
		auto info{parser.get_pos_info()};
		ASSERT_TRUE(raw.is_some());
		ASSERT_EQ(raw.except().str, ieml::String{"hello"});
		ASSERT_EQ(info.pos, str.cbegin() + 5);
		ASSERT_EQ(info.mark.line, 0);
		ASSERT_EQ(info.mark.symbol, 5);
	}
	{
		ieml::String str{"hello\n"};
		ieml::Parser parser{str};
		auto raw{parser.parse_raw()};
		auto info{parser.get_pos_info()};
		ASSERT_TRUE(raw.is_some());
		ASSERT_EQ(raw.except().str, ieml::String{"hello"});
		ASSERT_EQ(info.pos, str.cbegin() + 5);
		ASSERT_EQ(info.mark.line, 0);
		ASSERT_EQ(info.mark.symbol, 5);
	}
	{
		ieml::String str{"< \n"};
		ieml::Parser parser{str};
		auto raw{parser.parse_raw()};
		auto info{parser.get_pos_info()};
		ASSERT_FALSE(raw.is_some());
		ASSERT_EQ(info.pos, str.cbegin());
		ASSERT_EQ(info.mark.line, 0);
		ASSERT_EQ(info.mark.symbol, 0);
	}
}