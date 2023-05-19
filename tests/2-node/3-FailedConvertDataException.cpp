#include <gtest/gtest.h>

#include <IEML/node/exception/FailedDecodeData/FailedDecodeDataException.hpp>

TEST(Node, exception) {
	ieml::FailedDecodeDataException exception{ieml::Mark{2, 5}, ieml::getTypeInfo<int>()};
	ASSERT_EQ(exception.get_mark().line, 2);
	ASSERT_EQ(exception.get_mark().symbol, 5);
	ASSERT_EQ(exception.get_type_name(), std::string("int"));
	ASSERT_EQ(&exception.get_type_info(), &ieml::getTypeInfo<int>());
	ASSERT_EQ(exception.get_full_description(), std::string("2:5: Failed to convert node to 'int'"));
}