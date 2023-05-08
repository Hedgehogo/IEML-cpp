#include <gtest/gtest.h>

#include <IEML/node/Node/Node.hpp>

TEST(anchor, AnchorKeeper) {
	ieml::AnchorKeeper anchorKeeper{};
	ASSERT_TRUE(anchorKeeper.add(ieml::String{"key"}, ieml::NodeData{ieml::StringData{"value"}}));
	ASSERT_FALSE(anchorKeeper.add(ieml::String{"key"}, ieml::NodeData{ieml::StringData{"value"}}));
	
	ieml::Node* nodePtr{anchorKeeper.get(ieml::String{"key"})};
	ASSERT_FALSE(nodePtr == nullptr);
	ASSERT_TRUE(nodePtr->isString());
	ASSERT_EQ(nodePtr->as<ieml::StringData>().ok(), ieml::StringData{"value"});
	
	ieml::Node* incorrectNodePtr{anchorKeeper.get(ieml::String{"other-key"})};
	ASSERT_TRUE(incorrectNodePtr == nullptr);
}

TEST(anchor, AnchorKeeper_parent) {
	ieml::RcPtr<ieml::AnchorKeeper> parentAnchorKeeper{std::make_shared<ieml::AnchorKeeper>()};
	ASSERT_TRUE(parentAnchorKeeper->add(ieml::String{"key"}, ieml::NodeData{ieml::StringData{"value"}}));
	ASSERT_FALSE(parentAnchorKeeper->add(ieml::String{"key"}, ieml::NodeData{ieml::StringData{"value"}}));
	
	ieml::AnchorKeeper anchorKeeper{parentAnchorKeeper};
	ieml::Node* parentNodePtr{anchorKeeper.get(ieml::String{"key"})};
	ASSERT_FALSE(parentNodePtr == nullptr);
	ASSERT_TRUE(parentNodePtr->isString());
	ASSERT_EQ(parentNodePtr->as<ieml::StringData>().ok(), ieml::StringData{"value"});
	
	ieml::Node* parentIncorrectNodePtr{anchorKeeper.get(ieml::String{"other-key"})};
	ASSERT_TRUE(parentIncorrectNodePtr == nullptr);
	
	ASSERT_TRUE(anchorKeeper.add(ieml::String{"key"}, ieml::NodeData{ieml::StringData{"other-value"}}));
	ASSERT_FALSE(anchorKeeper.add(ieml::String{"key"}, ieml::NodeData{ieml::StringData{"other-value"}}));
	ASSERT_FALSE(parentAnchorKeeper->add(ieml::String{"key"}, ieml::NodeData{ieml::StringData{"value"}}));
	
	ieml::Node* nodePtr{anchorKeeper.get(ieml::String{"key"})};
	ASSERT_FALSE(nodePtr == nullptr);
	ASSERT_TRUE(nodePtr->isString());
	ASSERT_EQ(nodePtr->as<ieml::StringData>().ok(), ieml::StringData{"other-value"});
	
	ieml::Node* incorrectNodePtr{anchorKeeper.get(ieml::String{"other-key"})};
	ASSERT_TRUE(incorrectNodePtr == nullptr);
}