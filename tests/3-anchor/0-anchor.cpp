#include <gtest/gtest.h>

#include <IEML/parser.hpp>

TEST(anchor, AnchorKeeper) {
	ieml::AnchorKeeper anchor_keeper{};
	ASSERT_TRUE(anchor_keeper.add(ieml::String{"key"}, ieml::NodeData{ieml::StringData{"value"}}));
	ASSERT_FALSE(anchor_keeper.add(ieml::String{"key"}, ieml::NodeData{ieml::StringData{"value"}}));
	
	ieml::Node* node_ptr{anchor_keeper.get(ieml::String{"key"})};
	ASSERT_FALSE(node_ptr == nullptr);
	ASSERT_TRUE(node_ptr->is_string());
	ASSERT_EQ(node_ptr->as<ieml::StringData>().ok(), ieml::StringData{"value"});
	
	ieml::Node* incorrect_node_ptr{anchor_keeper.get(ieml::String{"other-key"})};
	ASSERT_TRUE(incorrect_node_ptr == nullptr);
}

TEST(anchor, AnchorKeeper_parent) {
	ieml::RcPtr<ieml::AnchorKeeper> parent_anchor_keeper{std::make_shared<ieml::AnchorKeeper>()};
	ASSERT_TRUE(parent_anchor_keeper->add(ieml::String{"key"}, ieml::NodeData{ieml::StringData{"value"}}));
	ASSERT_FALSE(parent_anchor_keeper->add(ieml::String{"key"}, ieml::NodeData{ieml::StringData{"value"}}));
	
	ieml::AnchorKeeper anchor_keeper{parent_anchor_keeper};
	ieml::Node* parent_node_ptr{anchor_keeper.get(ieml::String{"key"})};
	ASSERT_FALSE(parent_node_ptr == nullptr);
	ASSERT_TRUE(parent_node_ptr->is_string());
	ASSERT_EQ(parent_node_ptr->as<ieml::StringData>().ok(), ieml::StringData{"value"});
	
	ieml::Node* parent_incorrect_node_ptr{anchor_keeper.get(ieml::String{"other-key"})};
	ASSERT_TRUE(parent_incorrect_node_ptr == nullptr);
	
	ASSERT_TRUE(anchor_keeper.add(ieml::String{"key"}, ieml::NodeData{ieml::StringData{"other-value"}}));
	ASSERT_FALSE(anchor_keeper.add(ieml::String{"key"}, ieml::NodeData{ieml::StringData{"other-value"}}));
	ASSERT_FALSE(parent_anchor_keeper->add(ieml::String{"key"}, ieml::NodeData{ieml::StringData{"value"}}));
	
	ieml::Node* node_ptr{anchor_keeper.get(ieml::String{"key"})};
	ASSERT_FALSE(node_ptr == nullptr);
	ASSERT_TRUE(node_ptr->is_string());
	ASSERT_EQ(node_ptr->as<ieml::StringData>().ok(), ieml::StringData{"other-value"});
	
	ieml::Node* incorrect_node_ptr{anchor_keeper.get(ieml::String{"other-key"})};
	ASSERT_TRUE(incorrect_node_ptr == nullptr);
}