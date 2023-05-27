#include <gtest/gtest.h>

#include <IEML/node/Node/Node.hpp>

TEST(parser, Parser_parseGetAnchor) {
	{
		ieml::String str{"*anchor"};
		auto keeper{ieml::makeRcPtr<ieml::AnchorKeeper>()};
		ieml::Parser parser{str, keeper};
		auto getAnchor{parser.parseGetAnchor(2)};
		auto info{parser.getPosInfo()};
		ASSERT_TRUE(getAnchor.is_some());
		ASSERT_EQ(getAnchor.except().name_, ieml::String{"anchor"});
		ASSERT_EQ(getAnchor.except().keeper_, keeper);
		ASSERT_EQ(info.pos, str.cbegin() + 7);
		ASSERT_EQ(info.mark.line, 0);
		ASSERT_EQ(info.mark.symbol, 7);
	}
	{
		ieml::String str{"*anchor # hello"};
		auto keeper{ieml::makeRcPtr<ieml::AnchorKeeper>()};
		ieml::Parser parser{str, keeper};
		auto getAnchor{parser.parseGetAnchor(2)};
		auto info{parser.getPosInfo()};
		ASSERT_TRUE(getAnchor.is_some());
		ASSERT_EQ(getAnchor.except().name_, ieml::String{"anchor"});
		ASSERT_EQ(getAnchor.except().keeper_, keeper);
		ASSERT_EQ(info.pos, str.cbegin() + 15);
		ASSERT_EQ(info.mark.line, 0);
		ASSERT_EQ(info.mark.symbol, 15);
	}
	{
		ieml::String str{"*\n null"};
		ieml::Parser parser{str};
		auto getAnchor{parser.parseGetAnchor(2)};
		auto info{parser.getPosInfo()};
		ASSERT_FALSE(getAnchor.is_some());
		ASSERT_EQ(info.pos, str.cbegin());
		ASSERT_EQ(info.mark.line, 0);
		ASSERT_EQ(info.mark.symbol, 0);
	}
}