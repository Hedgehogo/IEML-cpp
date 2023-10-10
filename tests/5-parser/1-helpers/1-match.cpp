#include <gtest/gtest.h>

#include <IEML/parser/helpers/match/match.hpp>

static constexpr auto re = ctll::fixed_string{R"(cde)"};

static constexpr auto re_other = ctll::fixed_string{R"(cdf)"};

TEST(parser, helpers_match) {
	ieml::String str{"abcdefg"};
	{
		ieml::Mark mark{0, 2};
		ieml::String::const_iterator pos{str.begin() + 2};
		
		auto match = ieml::match_and_move<re>(pos, str.cend(), mark);
		ASSERT_TRUE(match.operator bool());
		ASSERT_EQ(match.begin(), str.begin() + 2);
		ASSERT_EQ(match.end(), str.begin() + 5);
		ASSERT_EQ(match.size(), 3);
		ASSERT_EQ(match.size(), 3);
		ASSERT_EQ(pos, str.begin() + 5);
		ASSERT_EQ(mark.symbol, 5);
		ASSERT_EQ(mark.line, 0);
	}
	
	{
		ieml::Mark mark{0, 2};
		ieml::String::const_iterator pos{str.begin() + 2};
		
		auto other_match = ieml::match_and_move<re_other>(pos, str.cend(), mark);
		ASSERT_FALSE(other_match.operator bool());
	}
	
	{
		ieml::Mark mark{0, 2};
		ieml::String::const_iterator pos{};
		
		auto match = ieml::match_and_move<re>(str.begin() + 2, pos, str.cend(), mark);
		ASSERT_TRUE(match.operator bool());
		ASSERT_EQ(match.begin(), str.begin() + 2);
		ASSERT_EQ(match.end(), str.begin() + 5);
		ASSERT_EQ(match.size(), 3);
		ASSERT_EQ(match.size(), 3);
		ASSERT_EQ(pos, str.begin() + 5);
		ASSERT_EQ(mark.symbol, 5);
		ASSERT_EQ(mark.line, 0);
	}
	
	{
		ieml::Mark mark{0, 2};
		ieml::String::const_iterator pos{};
		
		auto other_match = ieml::match_and_move<re_other>(str.begin() + 2, pos, str.cend(), mark);
		ASSERT_FALSE(other_match.operator bool());
	}
}