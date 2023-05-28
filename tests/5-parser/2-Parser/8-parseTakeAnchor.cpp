#include <gtest/gtest.h>

#include <IEML/parser.hpp>

TEST(parser, Parser_parseTakeAnchor) {
	{
		ieml::String str{"&anchor null"};
		auto keeper{ieml::makeRcPtr<ieml::AnchorKeeper>()};
		ieml::Parser parser{str, keeper};
		auto takeAnchor{parser.parseTakeAnchor(2)};
		auto info{parser.getPosInfo()};
		ASSERT_TRUE(takeAnchor.is_some());
		ASSERT_EQ(takeAnchor.except().name_, ieml::String{"anchor"});
		ASSERT_EQ(takeAnchor.except().keeper_, keeper);
		ASSERT_EQ(info.pos, str.cbegin() + 12);
		ASSERT_EQ(info.mark.line, 0);
		ASSERT_EQ(info.mark.symbol, 12);
		ASSERT_TRUE(keeper->get("anchor") != nullptr);
		ASSERT_TRUE(keeper->get("anchor")->isNull());
	}
	{
		ieml::String str{
			R"(&anchor
		null)"
		};
		auto keeper{ieml::makeRcPtr<ieml::AnchorKeeper>()};
		ieml::Parser parser{str, keeper};
		auto takeAnchor{parser.parseTakeAnchor(2)};
		auto info{parser.getPosInfo()};
		ASSERT_TRUE(takeAnchor.is_some());
		ASSERT_EQ(takeAnchor.except().name_, ieml::String{"anchor"});
		ASSERT_EQ(takeAnchor.except().keeper_, keeper);
		ASSERT_EQ(info.pos, str.cbegin() + 14);
		ASSERT_EQ(info.mark.line, 1);
		ASSERT_EQ(info.mark.symbol, 6);
		ASSERT_TRUE(keeper->get("anchor") != nullptr);
		ASSERT_TRUE(keeper->get("anchor")->isNull());
	}
	{
		ieml::String str{"&anchor null"};
		auto keeper{ieml::makeRcPtr<ieml::AnchorKeeper>()};
		keeper->add(ieml::String{"anchor"}, ieml::Node{ieml::NullData{}});
		ieml::Parser parser{str, keeper};
		EXPECT_THROW(parser.parseTakeAnchor(2), ieml::FailedParseException);
	}
	{
		ieml::String str{"&\n null"};
		auto keeper{ieml::makeRcPtr<ieml::AnchorKeeper>()};
		ieml::Parser parser{str, keeper};
		auto takeAnchor{parser.parseTakeAnchor(2)};
		auto info{parser.getPosInfo()};
		ASSERT_FALSE(takeAnchor.is_some());
		ASSERT_EQ(info.pos, str.cbegin());
		ASSERT_EQ(info.mark.line, 0);
		ASSERT_EQ(info.mark.symbol, 0);
		ASSERT_TRUE(keeper->get("\n") == nullptr);
	}
}