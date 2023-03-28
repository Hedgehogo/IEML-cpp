#include <gtest/gtest.h>
#include <IEML/node/exception/WithMark/WithMarkException.hpp>
#include <IEML/node/exception/NodeAnotherTypeException.hpp>

class TestWithMarkException : public ieml::WithMarkException {
public:
	TestWithMarkException(ieml::Mark mark) : ieml::WithMarkException(mark) {
	}
	
	ieml::String getDescription() const override {
		return "Test";
	}
};

TEST(node, exception) {
	TestWithMarkException withMarkException{ieml::Mark{1, 2}};
	ASSERT_EQ(withMarkException.getFullDescription(), ieml::String{"1:2: Test"});
	
	ieml::NodeAnotherTypeException exception{ieml::NodeType::String, ieml::NodeType::Raw};
	ASSERT_EQ(exception.getRequestedType(), ieml::NodeType::String);
	ASSERT_EQ(exception.getNodeType(), ieml::NodeType::Raw);
	ASSERT_EQ(exception.getFullDescription(), ieml::String{"Node of the 'Raw' type cannot be converted to a value of the 'String' type."});
}