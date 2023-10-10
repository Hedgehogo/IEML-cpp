#include <gtest/gtest.h>

#include <IEML/node/NodeType/NodeType.hpp>

TEST(node, NodeType) {
	ASSERT_EQ(ieml::get_string_from_node_type(ieml::NodeType::Null      ), std::string("Null"       ));
	ASSERT_EQ(ieml::get_string_from_node_type(ieml::NodeType::Raw       ), std::string("Raw"        ));
	ASSERT_EQ(ieml::get_string_from_node_type(ieml::NodeType::String    ), std::string("String"     ));
	ASSERT_EQ(ieml::get_string_from_node_type(ieml::NodeType::List      ), std::string("List"       ));
	ASSERT_EQ(ieml::get_string_from_node_type(ieml::NodeType::Map       ), std::string("Map"        ));
	ASSERT_EQ(ieml::get_string_from_node_type(ieml::NodeType::Tag       ), std::string("Tag"        ));
	ASSERT_EQ(ieml::get_string_from_node_type(ieml::NodeType::File      ), std::string("File"       ));
	ASSERT_EQ(ieml::get_string_from_node_type(ieml::NodeType::TakeAnchor), std::string("Take Anchor"));
	ASSERT_EQ(ieml::get_string_from_node_type(ieml::NodeType::GetAnchor ), std::string("Get Anchor" ));
	
	ASSERT_EQ(ieml::get_index_from_node_type(ieml::NodeType::Null      ), 0);
	ASSERT_EQ(ieml::get_index_from_node_type(ieml::NodeType::Raw       ), 1);
	ASSERT_EQ(ieml::get_index_from_node_type(ieml::NodeType::String    ), 2);
	ASSERT_EQ(ieml::get_index_from_node_type(ieml::NodeType::List      ), 3);
	ASSERT_EQ(ieml::get_index_from_node_type(ieml::NodeType::Map       ), 4);
	ASSERT_EQ(ieml::get_index_from_node_type(ieml::NodeType::Tag       ), 5);
	ASSERT_EQ(ieml::get_index_from_node_type(ieml::NodeType::File      ), 6);
	ASSERT_EQ(ieml::get_index_from_node_type(ieml::NodeType::TakeAnchor), 7);
	ASSERT_EQ(ieml::get_index_from_node_type(ieml::NodeType::GetAnchor ), 8);
	
	ASSERT_EQ(ieml::get_node_type_from_index(0), ieml::NodeType::Null      );
	ASSERT_EQ(ieml::get_node_type_from_index(1), ieml::NodeType::Raw       );
	ASSERT_EQ(ieml::get_node_type_from_index(2), ieml::NodeType::String    );
	ASSERT_EQ(ieml::get_node_type_from_index(3), ieml::NodeType::List      );
	ASSERT_EQ(ieml::get_node_type_from_index(4), ieml::NodeType::Map       );
	ASSERT_EQ(ieml::get_node_type_from_index(5), ieml::NodeType::Tag       );
	ASSERT_EQ(ieml::get_node_type_from_index(6), ieml::NodeType::File      );
	ASSERT_EQ(ieml::get_node_type_from_index(7), ieml::NodeType::TakeAnchor);
	ASSERT_EQ(ieml::get_node_type_from_index(8), ieml::NodeType::GetAnchor );
	ASSERT_EQ(ieml::get_node_type_from_index(9), ieml::NodeType::Null      );
}