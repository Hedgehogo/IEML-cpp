#include <gtest/gtest.h>

#include <IEML/parser/helpers/find/find.hpp>

TEST(parser, helpers_find) {
	ieml::String str{"hello world"};
	ieml::String::iterator iterFind{ieml::find(str.begin(), str.end(), 'l')};
	ASSERT_EQ(iterFind, str.begin() + 2);
	
	ieml::String::reverse_iterator rIterFind{ieml::find(str.rbegin(), str.rend(), 'l')};
	ASSERT_EQ(rIterFind, str.rbegin() + 1);
	
	ieml::String::iterator iterRfind{ieml::rfind(str.begin(), str.end(), 'l')};
	ASSERT_EQ(iterRfind, str.begin() + 9);
	
	ieml::String::reverse_iterator rIterRfind{ieml::rfind(str.rbegin(), str.rend(), 'l')};
	ASSERT_EQ(rIterRfind, str.rbegin() + 8);
	
	ieml::String::iterator iterFindSet{ieml::findSet<char, 'r', 'o'>(str.begin(), str.end())};
	ASSERT_EQ(iterFindSet, str.begin() + 4);
	
	ieml::String::reverse_iterator rIterFindSet{ieml::findSet<char, 'r', 'o'>(str.rbegin(), str.rend())};
	ASSERT_EQ(rIterFindSet, str.rbegin() + 2);
	
	ieml::String::iterator iterRFindSet{ieml::rfindSet<char, 'r', 'o'>(str.begin(), str.end())};
	ASSERT_EQ(iterRFindSet, str.begin() + 8);
	
	ieml::String::reverse_iterator rIterRFindSet{ieml::rfindSet<char, 'r', 'o'>(str.rbegin(), str.rend())};
	ASSERT_EQ(rIterRFindSet, str.rbegin() + 6);
}
