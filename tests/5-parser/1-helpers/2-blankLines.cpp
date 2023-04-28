#include <gtest/gtest.h>

#include <IEML/parser/helpers/blankLines/blankLines.hpp>

TEST(parser, helpers_blankLines_enter) {
	ieml::String str{"abc\ndef"};
	ASSERT_TRUE(ieml::isEnter(str.cbegin() + 3, str.cend()));
	ASSERT_FALSE(ieml::isEnter(str.cbegin() + 2, str.cend()));
	ASSERT_FALSE(ieml::isEnter(str.cbegin(), str.cend()));
	ASSERT_FALSE(ieml::isEnter(str.cend(), str.cend()));
	
	{
		ieml::Mark mark{15, 10};
		ieml::String::const_iterator iter{str.cbegin() + 3};
		ASSERT_TRUE(ieml::matchEnter(iter, str.cend(), mark));
		ASSERT_EQ(iter, str.cbegin() + 4);
		ASSERT_EQ(mark.symbol, 0);
		ASSERT_EQ(mark.line, 16);
	}
	
	{
		ieml::Mark mark{15, 10};
		ieml::String::const_iterator iter{str.cbegin() + 2};
		ASSERT_FALSE(ieml::matchEnter(iter, str.cend(), mark));
		ASSERT_EQ(iter, str.cbegin() + 2);
		ASSERT_EQ(mark.symbol, 10);
		ASSERT_EQ(mark.line, 15);
	}
	
	{
		ieml::Mark mark{15, 10};
		ieml::String::const_iterator iter{str.cbegin()};
		ASSERT_FALSE(ieml::matchEnter(iter, str.cend(), mark));
		ASSERT_EQ(iter, str.cbegin());
		ASSERT_EQ(mark.symbol, 10);
		ASSERT_EQ(mark.line, 15);
	}
	
	{
		ieml::Mark mark{15, 10};
		ieml::String::const_iterator iter{str.cend()};
		ASSERT_FALSE(ieml::matchEnter(iter, str.cend(), mark));
		ASSERT_EQ(iter, str.cend());
		ASSERT_EQ(mark.symbol, 10);
		ASSERT_EQ(mark.line, 15);
	}
}

TEST(parser, helpers_blankLines_indent) {

}