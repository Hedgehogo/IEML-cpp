#include <gtest/gtest.h>

#include <IEML/node/Mark/Mark.hpp>
#include <IEML/helpers/get_type_name/get_type_name.hpp>

class Test{};

template<>
struct ieml::TypeName<Test> {
	static ieml::String get() {
		return ieml::String{"Test Alias"};
	}
};

TEST(helpers, get_type_name) {
	ASSERT_EQ(ieml::get_type_name<ieml::Mark>(), std::string("ieml::Mark"));
	ASSERT_EQ(ieml::get_type_name<::Test>(), std::string("Test Alias"));
}