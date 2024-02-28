#include <gtest/gtest.h>

#include <IEML/node/Mark/Mark.hpp>
#include <IEML/helpers/unstable_type_name/unstable_type_name.hpp>

TEST(helpers, get_type_name) {
	ASSERT_EQ(ieml::unstable_type_name<ieml::Mark>(), std::string("ieml::Mark"));
}