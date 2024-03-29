#include <gtest/gtest.h>

#include <IEML/parser/helpers/blank_lines/blank_lines.hpp>

TEST(parser, helpers_blank_lines_enter) {
	ieml::String str{"abc\ndef"};
	ASSERT_TRUE(ieml::is_enter(str.cbegin() + 3, str.cend()));
	ASSERT_FALSE(ieml::is_enter(str.cbegin() + 2, str.cend()));
	ASSERT_FALSE(ieml::is_enter(str.cbegin(), str.cend()));
	ASSERT_FALSE(ieml::is_enter(str.cend(), str.cend()));
}

TEST(parser, helpers_blank_lines_enter_0) {
	ieml::String str{"abc\ndef"};
	ieml::Mark mark{15, 10};
	ieml::String::const_iterator iter{str.cbegin() + 3};
	ASSERT_TRUE(ieml::match_enter(iter, str.cend(), mark));
	ASSERT_EQ(iter, str.cbegin() + 4);
	ASSERT_EQ(mark.symbol, 0);
	ASSERT_EQ(mark.line, 16);
}

TEST(parser, helpers_blank_lines_enter_1) {
	ieml::String str{"abc\ndef"};
	ieml::Mark mark{15, 10};
	ieml::String::const_iterator iter{str.cbegin() + 2};
	ASSERT_FALSE(ieml::match_enter(iter, str.cend(), mark));
	ASSERT_EQ(iter, str.cbegin() + 2);
	ASSERT_EQ(mark.symbol, 10);
	ASSERT_EQ(mark.line, 15);
}

TEST(parser, helpers_blank_lines_enter_2) {
	ieml::String str{"abc\ndef"};
	ieml::Mark mark{15, 10};
	ieml::String::const_iterator iter{str.cbegin()};
	ASSERT_FALSE(ieml::match_enter(iter, str.cend(), mark));
	ASSERT_EQ(iter, str.cbegin());
	ASSERT_EQ(mark.symbol, 10);
	ASSERT_EQ(mark.line, 15);
}

TEST(parser, helpers_blank_lines_enter_3) {
	ieml::String str{"abc\ndef"};
	ieml::Mark mark{15, 10};
	ieml::String::const_iterator iter{str.cend()};
	ASSERT_FALSE(ieml::match_enter(iter, str.cend(), mark));
	ASSERT_EQ(iter, str.cend());
	ASSERT_EQ(mark.symbol, 10);
	ASSERT_EQ(mark.line, 15);
}

TEST(parser, helpers_blank_lines_indent_0) {
	ieml::String str{"\t\t\thello"};
	ieml::Mark mark{15, 10};
	ieml::String::const_iterator iter{str.cbegin()};
	ASSERT_TRUE(ieml::match_indent(iter, str.cend(), mark, 0));
	ASSERT_EQ(iter, str.cbegin());
	ASSERT_EQ(mark.symbol, 10);
	ASSERT_EQ(mark.line, 15);
}

TEST(parser, helpers_blank_lines_indent_1) {
	ieml::String str{"\t\t\thello"};
	ieml::Mark mark{15, 10};
	ieml::String::const_iterator iter{str.cbegin()};
	ASSERT_TRUE(ieml::match_indent(iter, str.cend(), mark, 2));
	ASSERT_EQ(iter, str.cbegin() + 2);
	ASSERT_EQ(mark.symbol, 12);
	ASSERT_EQ(mark.line, 15);
}

TEST(parser, helpers_blank_lines_indent_2) {
	ieml::String str{"\t\t\thello"};
	ieml::Mark mark{15, 10};
	ieml::String::const_iterator iter{str.cbegin()};
	ASSERT_TRUE(ieml::match_indent(iter, str.cend(), mark, 3));
	ASSERT_EQ(iter, str.cbegin() + 3);
	ASSERT_EQ(mark.symbol, 13);
	ASSERT_EQ(mark.line, 15);
}

TEST(parser, helpers_blank_lines_indent_3) {
	ieml::String str{"\t\t\thello"};
	ieml::Mark mark{15, 10};
	ieml::String::const_iterator iter{str.cbegin()};
	ASSERT_FALSE(ieml::match_indent(iter, str.cend(), mark, 4));
	ASSERT_EQ(iter, str.cbegin());
	ASSERT_EQ(mark.symbol, 10);
	ASSERT_EQ(mark.line, 15);
}

TEST(parser, helpers_blank_lines_blank_line_0) {
	ieml::String str{"\t  hello"};
	ieml::Mark mark{15, 10};
	ieml::String::const_iterator iter{str.cbegin()};
	ASSERT_TRUE(ieml::skip_blank_line(iter, str.cend(), mark));
	ASSERT_EQ(iter, str.cbegin() + 3);
	ASSERT_EQ(mark.symbol, 13);
	ASSERT_EQ(mark.line, 15);
}

TEST(parser, helpers_blank_lines_blank_line_1) {
	ieml::String str{"\t # fg\n b"};
	ieml::Mark mark{15, 10};
	ieml::String::const_iterator iter{str.cbegin()};
	ASSERT_TRUE(ieml::skip_blank_line(iter, str.cend(), mark));
	ASSERT_EQ(iter, str.cbegin() + 6);
	ASSERT_EQ(mark.symbol, 16);
	ASSERT_EQ(mark.line, 15);
}

TEST(parser, helpers_blank_lines_blank_line_2) {
	ieml::String str{"#sadh "};
	ieml::Mark mark{15, 10};
	ieml::String::const_iterator iter{str.cbegin()};
	ASSERT_FALSE(ieml::skip_blank_line(iter, str.cend(), mark));
	ASSERT_EQ(iter, str.cbegin());
	ASSERT_EQ(mark.symbol, 10);
	ASSERT_EQ(mark.line, 15);
}

TEST(parser, helpers_blank_lines_blank_lines_ln_0) {
	ieml::String str{
		" # hello\n"
		" \t \t \n"
		" world"
	};
	ieml::Mark mark{15, 10};
	ieml::String::const_iterator iter{str.cbegin()};
	ASSERT_TRUE(ieml::skip_blank_lines_ln(iter, str.cend(), mark));
	ASSERT_EQ(iter, str.cend() - 6);
	ASSERT_EQ(mark.symbol, 0);
	ASSERT_EQ(mark.line, 17);
}

TEST(parser, helpers_blank_lines_blank_lines_ln_1) {
	ieml::String str{
		" #hello\n"
		"hello"
	};
	ieml::Mark mark{15, 10};
	ieml::String::const_iterator iter{str.cbegin()};
	ASSERT_FALSE(ieml::skip_blank_lines_ln(iter, str.cend(), mark));
	ASSERT_EQ(iter, str.begin());
	ASSERT_EQ(mark.symbol, 10);
	ASSERT_EQ(mark.line, 15);
}