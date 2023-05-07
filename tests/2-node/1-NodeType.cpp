#include <gtest/gtest.h>

#include <IEML/node/NodeType/NodeType.hpp>

TEST(node, NodeType) {
	ASSERT_EQ(ieml::getStringFromNodeType(ieml::NodeType::Null      ), std::string("Null"       ));
	ASSERT_EQ(ieml::getStringFromNodeType(ieml::NodeType::Raw       ), std::string("Raw"        ));
	ASSERT_EQ(ieml::getStringFromNodeType(ieml::NodeType::String    ), std::string("String"     ));
	ASSERT_EQ(ieml::getStringFromNodeType(ieml::NodeType::List      ), std::string("List"       ));
	ASSERT_EQ(ieml::getStringFromNodeType(ieml::NodeType::Map       ), std::string("Map"        ));
	ASSERT_EQ(ieml::getStringFromNodeType(ieml::NodeType::Tag       ), std::string("Tag"        ));
	ASSERT_EQ(ieml::getStringFromNodeType(ieml::NodeType::File      ), std::string("File"       ));
	ASSERT_EQ(ieml::getStringFromNodeType(ieml::NodeType::TakeAnchor), std::string("Take Anchor"));
	ASSERT_EQ(ieml::getStringFromNodeType(ieml::NodeType::GetAnchor ), std::string("Get Anchor" ));
	
	ASSERT_EQ(ieml::getIndexFromNodeType(ieml::NodeType::Null      ), 0);
	ASSERT_EQ(ieml::getIndexFromNodeType(ieml::NodeType::Raw       ), 1);
	ASSERT_EQ(ieml::getIndexFromNodeType(ieml::NodeType::String    ), 2);
	ASSERT_EQ(ieml::getIndexFromNodeType(ieml::NodeType::List      ), 3);
	ASSERT_EQ(ieml::getIndexFromNodeType(ieml::NodeType::Map       ), 4);
	ASSERT_EQ(ieml::getIndexFromNodeType(ieml::NodeType::Tag       ), 5);
	ASSERT_EQ(ieml::getIndexFromNodeType(ieml::NodeType::File      ), 6);
	ASSERT_EQ(ieml::getIndexFromNodeType(ieml::NodeType::TakeAnchor), 7);
	ASSERT_EQ(ieml::getIndexFromNodeType(ieml::NodeType::GetAnchor ), 8);
	
	ASSERT_EQ(ieml::getNodeTypeFromIndex(0), ieml::NodeType::Null      );
	ASSERT_EQ(ieml::getNodeTypeFromIndex(1), ieml::NodeType::Raw       );
	ASSERT_EQ(ieml::getNodeTypeFromIndex(2), ieml::NodeType::String    );
	ASSERT_EQ(ieml::getNodeTypeFromIndex(3), ieml::NodeType::List      );
	ASSERT_EQ(ieml::getNodeTypeFromIndex(4), ieml::NodeType::Map       );
	ASSERT_EQ(ieml::getNodeTypeFromIndex(5), ieml::NodeType::Tag       );
	ASSERT_EQ(ieml::getNodeTypeFromIndex(6), ieml::NodeType::File      );
	ASSERT_EQ(ieml::getNodeTypeFromIndex(7), ieml::NodeType::TakeAnchor);
	ASSERT_EQ(ieml::getNodeTypeFromIndex(8), ieml::NodeType::GetAnchor );
	ASSERT_EQ(ieml::getNodeTypeFromIndex(9), ieml::NodeType::Null      );
}