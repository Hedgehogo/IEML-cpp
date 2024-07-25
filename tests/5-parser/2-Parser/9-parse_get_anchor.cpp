#include <gtest/gtest.h>

#include <IEML/parser.hpp>

TEST(parser, Parser_parse_get_anchor) {
	{
		ieml::String str{"@anchor"};
		auto keeper{ieml::make_rc_ptr<ieml::AnchorKeeper>()};
		ieml::Parser parser{str, keeper};
		auto get_anchor{parser.parse_get_anchor(2)};
		auto info{parser.get_pos_info()};
		ASSERT_TRUE(get_anchor.is_some());
		ASSERT_EQ(get_anchor.except().name_, ieml::String{"anchor"});
		ASSERT_EQ(get_anchor.except().keeper_.lock(), keeper);
		ASSERT_EQ(info.pos, str.cbegin() + 7);
		ASSERT_EQ(info.mark.line, 0);
		ASSERT_EQ(info.mark.symbol, 7);
	}
	{
		ieml::String str{"@anchor # hello"};
		auto keeper{ieml::make_rc_ptr<ieml::AnchorKeeper>()};
		ieml::Parser parser{str, keeper};
		auto get_anchor{parser.parse_get_anchor(2)};
		auto info{parser.get_pos_info()};
		ASSERT_TRUE(get_anchor.is_some());
		ASSERT_EQ(get_anchor.except().name_, ieml::String{"anchor # hello"});
		ASSERT_EQ(get_anchor.except().keeper_.lock(), keeper);
		ASSERT_EQ(info.pos, str.cbegin() + 15);
		ASSERT_EQ(info.mark.line, 0);
		ASSERT_EQ(info.mark.symbol, 15);
	}
}