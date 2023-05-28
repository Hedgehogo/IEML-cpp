#include <gtest/gtest.h>

#include <IEML/parser.hpp>

TEST(parser, Parser_end) {
	ieml::String str{"hello"};
	ieml::Parser parser{str};
	
	ASSERT_EQ(parser.end(), str.cend());
}

TEST(parser, Parser_getPosInfo) {
	ieml::String str{"hello"};
	ieml::Parser parser{str};
	
	auto info{parser.getPosInfo()};
	ASSERT_EQ(info.pos, str.cbegin());
}

TEST(parser, Parser_Parser) {
	ieml::String str{"hello"};
	ieml::Parser parser{str};
	
	parser.setPosInfo({str.cbegin() + 2, {2, 5}});
	
	auto info{parser.getPosInfo()};
	ASSERT_EQ(info.pos, str.cbegin() + 2);
	ASSERT_EQ(info.mark.line, 2);
	ASSERT_EQ(info.mark.symbol, 5);
	
	ASSERT_EQ(parser.end(), str.cend());
}