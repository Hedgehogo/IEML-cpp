#include <gtest/gtest.h>

#include <IEML/parser.hpp>

TEST(parser, Parser_parse_classic_string) {
	{
		ieml::String str{
			R"("hello")"
		};
		ieml::Parser parser{str};
		auto classic_string{parser.parse_classic_string(2)};
		auto info{parser.get_pos_info()};
		ASSERT_TRUE(classic_string.is_some());
		ASSERT_EQ(classic_string.except(), ieml::String{"hello"});
		ASSERT_EQ(info.pos, str.cbegin() + 7);
		ASSERT_EQ(info.mark.line, 0);
		ASSERT_EQ(info.mark.symbol, 7);
	}
	{
		ieml::String str{
			R"("hello"hello)"
		};
		ieml::Parser parser{str};
		auto classic_string{parser.parse_classic_string(2)};
		auto info{parser.get_pos_info()};
		ASSERT_TRUE(classic_string.is_some());
		ASSERT_EQ(classic_string.except(), ieml::String{"hello"});
		ASSERT_EQ(info.pos, str.cbegin() + 7);
		ASSERT_EQ(info.mark.line, 0);
		ASSERT_EQ(info.mark.symbol, 7);
	}
	{
		ieml::String str{
			R"( "hello")"
		};
		ieml::Parser parser{str};
		auto classic_string{parser.parse_classic_string(2)};
		auto info{parser.get_pos_info()};
		ASSERT_FALSE(classic_string.is_some());
		ASSERT_EQ(info.pos, str.cbegin());
		ASSERT_EQ(info.mark.line, 0);
		ASSERT_EQ(info.mark.symbol, 0);
	}
	{
		ieml::String str{
			R"("hello
		world")"
		};
		ieml::Parser parser{str};
		auto classic_string{parser.parse_classic_string(2)};
		auto info{parser.get_pos_info()};
		ASSERT_TRUE(classic_string.is_some());
		ASSERT_EQ(classic_string.except(), ieml::String{"hello\nworld"});
		ASSERT_EQ(info.pos, str.cbegin() + 15);
		ASSERT_EQ(info.mark.line, 1);
		ASSERT_EQ(info.mark.symbol, 8);
	}
	{
		ieml::String str{
			R"("hello
			world")"
		};
		ieml::Parser parser{str};
		auto classic_string{parser.parse_classic_string(2)};
		auto info{parser.get_pos_info()};
		ASSERT_TRUE(classic_string.is_some());
		ASSERT_EQ(classic_string.except(), ieml::String{"hello\n\tworld"});
		ASSERT_EQ(info.pos, str.cbegin() + 16);
		ASSERT_EQ(info.mark.line, 1);
		ASSERT_EQ(info.mark.symbol, 9);
	}
	{
		ieml::String str{
			R"("hello
	world")"
		};
		ieml::Parser parser{str};
		auto classic_string{parser.parse_classic_string(2)};
		auto info{parser.get_pos_info()};
		ASSERT_FALSE(classic_string.is_some());
		ASSERT_EQ(info.pos, str.cbegin());
		ASSERT_EQ(info.mark.line, 0);
		ASSERT_EQ(info.mark.symbol, 0);
	}
	{
		ieml::String str{
			R"("hello \
		world")"
		};
		ieml::Parser parser{str};
		auto classic_string{parser.parse_classic_string(2)};
		auto info{parser.get_pos_info()};
		ASSERT_TRUE(classic_string.is_some());
		ASSERT_EQ(classic_string.except(), ieml::String{"hello world"});
		ASSERT_EQ(info.pos, str.cbegin() + 17);
		ASSERT_EQ(info.mark.line, 1);
		ASSERT_EQ(info.mark.symbol, 8);
	}
	{
		ieml::String str{
			R"("hello \"world\"")"
		};
		ieml::Parser parser{str};
		auto classic_string{parser.parse_classic_string(2)};
		auto info{parser.get_pos_info()};
		ASSERT_TRUE(classic_string.is_some());
		ASSERT_EQ(classic_string.except(), ieml::String{"hello \"world\""});
		ASSERT_EQ(info.pos, str.cbegin() + 17);
		ASSERT_EQ(info.mark.line, 0);
		ASSERT_EQ(info.mark.symbol, 17);
	}
	{
		ieml::String str{
			R"("hello \world")"
		};
		ieml::Parser parser{str};
		auto classic_string{parser.parse_classic_string(2)};
		auto info{parser.get_pos_info()};
		ASSERT_TRUE(classic_string.is_some());
		ASSERT_EQ(classic_string.except(), ieml::String{"hello \\world"});
		ASSERT_EQ(info.pos, str.cbegin() + 14);
		ASSERT_EQ(info.mark.line, 0);
		ASSERT_EQ(info.mark.symbol, 14);
	}
}