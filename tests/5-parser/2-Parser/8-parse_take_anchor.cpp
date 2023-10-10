#include <gtest/gtest.h>

#include <IEML/parser.hpp>

TEST(parser, Parser_parse_take_anchor) {
	{
		ieml::String str{"&anchor null"};
		auto keeper{ieml::make_rc_ptr<ieml::AnchorKeeper>()};
		ieml::Parser parser{str, keeper};
		auto take_anchor{parser.parse_take_anchor(2)};
		auto info{parser.get_pos_info()};
		ASSERT_TRUE(take_anchor.is_some());
		ASSERT_EQ(take_anchor.except().name_, ieml::String{"anchor"});
		ASSERT_EQ(take_anchor.except().keeper_.lock(), keeper);
		ASSERT_EQ(info.pos, str.cbegin() + 12);
		ASSERT_EQ(info.mark.line, 0);
		ASSERT_EQ(info.mark.symbol, 12);
		ASSERT_TRUE(keeper->get("anchor") != nullptr);
		ASSERT_TRUE(keeper->get("anchor")->is_null());
	}
	{
		ieml::String str{
			R"(&anchor
		null)"
		};
		auto keeper{ieml::make_rc_ptr<ieml::AnchorKeeper>()};
		ieml::Parser parser{str, keeper};
		auto take_anchor{parser.parse_take_anchor(2)};
		auto info{parser.get_pos_info()};
		ASSERT_TRUE(take_anchor.is_some());
		ASSERT_EQ(take_anchor.except().name_, ieml::String{"anchor"});
		ASSERT_EQ(take_anchor.except().keeper_.lock(), keeper);
		ASSERT_EQ(info.pos, str.cbegin() + 14);
		ASSERT_EQ(info.mark.line, 1);
		ASSERT_EQ(info.mark.symbol, 6);
		ASSERT_TRUE(keeper->get("anchor") != nullptr);
		ASSERT_TRUE(keeper->get("anchor")->is_null());
	}
	{
		ieml::String str{"&anchor null"};
		auto keeper{ieml::make_rc_ptr<ieml::AnchorKeeper>()};
		keeper->add(ieml::String{"anchor"}, ieml::Node{ieml::NullData{}});
		ieml::Parser parser{str, keeper};
		EXPECT_THROW(parser.parse_take_anchor(2), ieml::FailedParseException);
	}
	{
		ieml::String str{"&\n null"};
		auto keeper{ieml::make_rc_ptr<ieml::AnchorKeeper>()};
		ieml::Parser parser{str, keeper};
		auto take_anchor{parser.parse_take_anchor(2)};
		auto info{parser.get_pos_info()};
		ASSERT_FALSE(take_anchor.is_some());
		ASSERT_EQ(info.pos, str.cbegin());
		ASSERT_EQ(info.mark.line, 0);
		ASSERT_EQ(info.mark.symbol, 0);
		ASSERT_TRUE(keeper->get("\n") == nullptr);
	}
}