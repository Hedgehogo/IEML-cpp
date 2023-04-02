#include <gtest/gtest.h>

#include <IEML/node/Mark/Mark.hpp>

TEST(node, Mark) {
	ieml::Mark mark1{1, 1};
	mark1.enter();
	ASSERT_EQ(mark1.line, 2);
	ASSERT_EQ(mark1.symbol, 0);
	
	ieml::Mark mark2{1, 1};
	ieml::String str{"12"};
	ieml::String::const_iterator pos{str.cbegin()};
	mark2.enter(pos);
	ASSERT_EQ(mark1.line, 2);
	ASSERT_EQ(mark1.symbol, 0);
	ASSERT_EQ(*pos, '2');
}