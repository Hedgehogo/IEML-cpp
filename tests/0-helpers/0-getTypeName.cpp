#include <gtest/gtest.h>
#include <IEML/node/Mark/Mark.hpp>
#include <IEML/helpers/getTypeName/getTypeName.hpp>

TEST(helpers, getTypeName) {
	ASSERT_EQ(ieml::getTypeName<ieml::Mark>(), std::string("ieml::Mark"));
}