#include <gtest/gtest.h>

#include <IEML/parser/helpers/find/find.hpp>

TEST(parser, helpers_find) {
	ieml::String str{"hello world"};
	ieml::String::iterator iter_find{ieml::find(str.begin(), str.end(), 'l')};
	ASSERT_EQ(iter_find, str.begin() + 2);
	
	ieml::String::reverse_iterator r_iter_find{ieml::find(str.rbegin(), str.rend(), 'l')};
	ASSERT_EQ(r_iter_find, str.rbegin() + 1);
	
	ieml::String::iterator iter_rfind{ieml::rfind(str.begin(), str.end(), 'l')};
	ASSERT_EQ(iter_rfind, str.begin() + 9);
	
	ieml::String::reverse_iterator r_iter_rfind{ieml::rfind(str.rbegin(), str.rend(), 'l')};
	ASSERT_EQ(r_iter_rfind, str.rbegin() + 8);
	
	ieml::String::iterator iter_find_set{ieml::find_set<char, 'r', 'o'>(str.begin(), str.end())};
	ASSERT_EQ(iter_find_set, str.begin() + 4);
	
	ieml::String::reverse_iterator r_iter_find_set{ieml::find_set<char, 'r', 'o'>(str.rbegin(), str.rend())};
	ASSERT_EQ(r_iter_find_set, str.rbegin() + 2);
	
	ieml::String::iterator iterRFindSet{ieml::rfind_set<char, 'r', 'o'>(str.begin(), str.end())};
	ASSERT_EQ(iterRFindSet, str.begin() + 8);
	
	ieml::String::reverse_iterator r_iterRFindSet{ieml::rfind_set<char, 'r', 'o'>(str.rbegin(), str.rend())};
	ASSERT_EQ(r_iterRFindSet, str.rbegin() + 6);
}
