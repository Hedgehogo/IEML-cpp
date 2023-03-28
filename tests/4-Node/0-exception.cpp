#include <gtest/gtest.h>

#include <IEML/node/Node/exception/FailedConvertDataException.hpp>

TEST(Node, exception) {
	ieml::FailedConvertDataException exception{ieml::Mark{2, 5}, ieml::getTypeInfo<int>()};
	ASSERT_EQ(exception.getMark().line, 2);
	ASSERT_EQ(exception.getMark().symbol, 5);
	ASSERT_EQ(exception.getTypeName(), std::string("int"));
	ASSERT_EQ(&exception.getTypeInfo(), &ieml::getTypeInfo<int>());
	ASSERT_EQ(exception.getFullDescription(), std::string("2:5: Failed to convert node to 'int'"));
}