#include <gtest/gtest.h>

#include <IEML/anchor/AnchorKeeper/AnchorKeeper.hpp>

TEST(anchor, AnchorKeeper) {
	ieml::AnchorKeeper anchorKeeper{};
	ASSERT_TRUE(anchorKeeper.add(ieml::String{"key"}, ieml::NodeData{ieml::StringData{"value"}}));
	ASSERT_FALSE(anchorKeeper.add(ieml::String{"key"}, ieml::NodeData{ieml::StringData{"value"}}));
	
	ieml::NodeData* dataPtr{anchorKeeper.get(ieml::String{"key"})};
	ASSERT_FALSE(dataPtr == nullptr);
	
	ieml::StringData* stringPtr{std::get_if<ieml::StringData>(dataPtr)};
	ASSERT_FALSE(stringPtr == nullptr);
	
	ieml::StringData& string{*stringPtr};
	ASSERT_EQ(string, ieml::StringData{"value"});
	
	ieml::NodeData* incorrectDataPtr{anchorKeeper.get(ieml::String{"other-key"})};
	ASSERT_TRUE(incorrectDataPtr == nullptr);
}

TEST(anchor, AnchorKeeper_parent) {
	ieml::Rc<ieml::AnchorKeeper> parentAnchorKeeper{std::make_shared<ieml::AnchorKeeper>()};
	ASSERT_TRUE(parentAnchorKeeper->add(ieml::String{"key"}, ieml::NodeData{ieml::StringData{"value"}}));
	ASSERT_FALSE(parentAnchorKeeper->add(ieml::String{"key"}, ieml::NodeData{ieml::StringData{"value"}}));
	
	ieml::AnchorKeeper anchorKeeper{parentAnchorKeeper};
	ieml::NodeData* parentDataPtr{anchorKeeper.get(ieml::String{"key"})};
	ASSERT_FALSE(parentDataPtr == nullptr);
	
	ieml::StringData* parentStringPtr{std::get_if<ieml::StringData>(parentDataPtr)};
	ASSERT_FALSE(parentStringPtr == nullptr);
	
	ieml::StringData& parentString{*parentStringPtr};
	ASSERT_EQ(parentString, ieml::StringData{"value"});
	
	ieml::NodeData* parentIncorrectDataPtr{anchorKeeper.get(ieml::String{"other-key"})};
	ASSERT_TRUE(parentIncorrectDataPtr == nullptr);
	
	ASSERT_TRUE(anchorKeeper.add(ieml::String{"key"}, ieml::NodeData{ieml::StringData{"other-value"}}));
	ASSERT_FALSE(anchorKeeper.add(ieml::String{"key"}, ieml::NodeData{ieml::StringData{"other-value"}}));
	ASSERT_FALSE(parentAnchorKeeper->add(ieml::String{"key"}, ieml::NodeData{ieml::StringData{"value"}}));
	
	ieml::NodeData* dataPtr{anchorKeeper.get(ieml::String{"key"})};
	ASSERT_FALSE(dataPtr == nullptr);
	
	ieml::StringData* stringPtr{std::get_if<ieml::StringData>(dataPtr)};
	ASSERT_FALSE(stringPtr == nullptr);
	
	ieml::StringData& string{*stringPtr};
	ASSERT_EQ(string, ieml::StringData{"other-value"});
	
	ieml::NodeData* incorrectDataPtr{anchorKeeper.get(ieml::String{"other-key"})};
	ASSERT_TRUE(incorrectDataPtr == nullptr);
}