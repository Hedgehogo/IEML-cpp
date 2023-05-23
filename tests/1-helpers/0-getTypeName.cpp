#include <gtest/gtest.h>

#include <IEML/node/Mark/Mark.hpp>
#include <IEML/helpers/getTypeName/getTypeName.hpp>

class Test{};

template<>
struct ieml::TypeName<Test> {
	static ieml::String get() {
		return ieml::String{"Test Alias"};
	}
};

TEST(helpers, getTypeName) {
	ASSERT_EQ(ieml::getTypeName<ieml::Mark>(), std::string("ieml::Mark"));
	ASSERT_EQ(ieml::getTypeName<::Test>(), std::string("Test Alias"));
}