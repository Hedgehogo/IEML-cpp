#include <gtest/gtest.h>

#include <IEML/node/exception/WithMark/WithMarkException.hpp>
#include <IEML/node/exception/NodeAnotherType/NodeAnotherTypeException.hpp>

class TestWithMarkException : public ieml::WithMarkException {
public:
	TestWithMarkException(ieml::Mark mark) : ieml::WithMarkException(mark) {
	}
	
	ieml::String get_description() const override {
		return "Test";
	}
};

TEST(node, exception) {
	TestWithMarkException withMarkException{ieml::Mark{1, 2}};
	ASSERT_EQ(withMarkException.get_full_description(), ieml::String{"1:2: Test"});
	
	ieml::NodeAnotherTypeException exception{ieml::Mark{2, 5}, ieml::NodeType::String, ieml::NodeType::Raw};
	ASSERT_EQ(exception.get_mark().line, 2);
	ASSERT_EQ(exception.get_mark().symbol, 5);
	ASSERT_EQ(exception.get_requested_type(), ieml::NodeType::String);
	ASSERT_EQ(exception.get_node_type(), ieml::NodeType::Raw);
	ASSERT_EQ(exception.get_full_description(), ieml::String{"2:5: Node of the 'Raw' type cannot be converted to a value of the 'String' type."});
}