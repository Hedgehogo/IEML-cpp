#include <gtest/gtest.h>

#include <IEML/parser.hpp>

TEST(parser, Parser_parse_scalar) {
	{
		ieml::String str{R"(null # hello)"};
		ieml::Parser parser{str};
		auto scalar{parser.parse_scalar(2)};
		auto info{parser.get_pos_info()};
		ASSERT_EQ(scalar.data_.index(), 0);
		ASSERT_EQ(info.pos, str.cbegin() + 12);
		ASSERT_EQ(info.mark.line, 0);
		ASSERT_EQ(info.mark.symbol, 12);
	}
	{
		ieml::String str{R"(hello # hello)"};
		ieml::Parser parser{str};
		auto scalar{parser.parse_scalar(2)};
		auto info{parser.get_pos_info()};
		ASSERT_EQ(scalar.data_.index(), 1);
		ASSERT_EQ(std::get_if<1>(&scalar.data_)->str, ieml::String{"hello # hello"});
		ASSERT_EQ(info.pos, str.cbegin() + 13);
		ASSERT_EQ(info.mark.line, 0);
		ASSERT_EQ(info.mark.symbol, 13);
	}
	{
		ieml::String str{R"(> hello # hello)"};
		ieml::Parser parser{str};
		auto scalar{parser.parse_scalar(2)};
		auto info{parser.get_pos_info()};
		ASSERT_EQ(scalar.data_.index(), 2);
		ASSERT_EQ(*std::get_if<2>(&scalar.data_), ieml::String{"hello # hello"});
		ASSERT_EQ(info.pos, str.cbegin() + 15);
		ASSERT_EQ(info.mark.line, 0);
		ASSERT_EQ(info.mark.symbol, 15);
	}
	{
		ieml::String str{
			R"(>> # hello
		hello)"
		};
		ieml::Parser parser{str};
		auto scalar{parser.parse_scalar(2)};
		auto info{parser.get_pos_info()};
		ASSERT_EQ(scalar.data_.index(), 2);
		ASSERT_EQ(*std::get_if<2>(&scalar.data_), ieml::String{"hello"});
		ASSERT_EQ(info.pos, str.cbegin() + 18);
		ASSERT_EQ(info.mark.line, 1);
		ASSERT_EQ(info.mark.symbol, 7);
	}
	{
		ieml::String str{R"("hello" # hello)"};
		ieml::Parser parser{str};
		auto scalar{parser.parse_scalar(2)};
		auto info{parser.get_pos_info()};
		ASSERT_EQ(scalar.data_.index(), 2);
		ASSERT_EQ(*std::get_if<2>(&scalar.data_), ieml::String{"hello"});
		ASSERT_EQ(info.pos, str.cbegin() + 15);
		ASSERT_EQ(info.mark.line, 0);
		ASSERT_EQ(info.mark.symbol, 15);
	}
}