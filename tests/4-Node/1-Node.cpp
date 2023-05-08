#include <gtest/gtest.h>

#include <IEML/node/Node/Node.hpp>

TEST(Node, Node_0_Null) {
	ieml::Node node{ieml::NullData{}, ieml::Mark{2, 5}};
	ASSERT_EQ(node.getMark().line, 2);
	ASSERT_EQ(node.getMark().symbol, 5);
	
	ASSERT_TRUE(node.isNull());
	ASSERT_FALSE(node.isRaw());
	ASSERT_FALSE(node.isString());
	ASSERT_FALSE(node.isList());
	ASSERT_FALSE(node.isMap());
	ASSERT_FALSE(node.isFile());
	ASSERT_FALSE(node.isWithTag());
	ASSERT_FALSE(node.isTakeAnchor());
	ASSERT_FALSE(node.isGetAnchor());
}

TEST(Node, Node_1_Raw) {
	ieml::Node node{ieml::RawData{}};
	
	ASSERT_FALSE(node.isNull());
	ASSERT_TRUE(node.isRaw());
	ASSERT_FALSE(node.isString());
	ASSERT_FALSE(node.isList());
	ASSERT_FALSE(node.isMap());
	ASSERT_FALSE(node.isFile());
	ASSERT_FALSE(node.isWithTag());
	ASSERT_FALSE(node.isTakeAnchor());
	ASSERT_FALSE(node.isGetAnchor());
}

TEST(Node, Node_2_String) {
	ieml::Node node{ieml::StringData{}};
	
	ASSERT_FALSE(node.isNull());
	ASSERT_FALSE(node.isRaw());
	ASSERT_TRUE(node.isString());
	ASSERT_FALSE(node.isList());
	ASSERT_FALSE(node.isMap());
	ASSERT_FALSE(node.isFile());
	ASSERT_FALSE(node.isWithTag());
	ASSERT_FALSE(node.isTakeAnchor());
	ASSERT_FALSE(node.isGetAnchor());
}

TEST(Node, Node_3_List) {
	ieml::Node node{ieml::ListData{ieml::Node{ieml::NullData{}}}};
	
	ASSERT_FALSE(node.isNull());
	ASSERT_FALSE(node.isRaw());
	ASSERT_FALSE(node.isString());
	ASSERT_TRUE(node.isList());
	ASSERT_FALSE(node.isMap());
	ASSERT_FALSE(node.isFile());
	ASSERT_FALSE(node.isWithTag());
	ASSERT_FALSE(node.isTakeAnchor());
	ASSERT_FALSE(node.isGetAnchor());
	
	ASSERT_EQ(node.getListSize(), 1);
	ASSERT_EQ(node.getSize(), 1);
	
	ieml::Node & elem{node.at(0)};
	ASSERT_TRUE(elem.isDefined());
	ASSERT_EQ(&elem, &node[0]);
	
	ASSERT_TRUE(elem.isNull());
	ASSERT_FALSE(elem.isRaw());
	ASSERT_FALSE(elem.isString());
	ASSERT_FALSE(elem.isList());
	ASSERT_FALSE(elem.isMap());
	ASSERT_FALSE(elem.isFile());
	ASSERT_FALSE(elem.isWithTag());
	ASSERT_FALSE(elem.isTakeAnchor());
	ASSERT_FALSE(elem.isGetAnchor());
	
	ieml::Node & incorrectElem{node.at(1)};
	ASSERT_FALSE(incorrectElem.isDefined());
}

TEST(Node, Node_4_Map) {
	ieml::Node node{ieml::MapData{{ieml::String{"key"}, ieml::Node{ieml::NullData{}}}}};
	
	ASSERT_FALSE(node.isNull());
	ASSERT_FALSE(node.isRaw());
	ASSERT_FALSE(node.isString());
	ASSERT_FALSE(node.isList());
	ASSERT_TRUE(node.isMap());
	ASSERT_FALSE(node.isFile());
	ASSERT_FALSE(node.isWithTag());
	ASSERT_FALSE(node.isTakeAnchor());
	ASSERT_FALSE(node.isGetAnchor());
	
	ASSERT_EQ(node.getMapSize(), 1);
	ASSERT_EQ(node.getSize(), 1);
	
	ieml::Node & elem{node.at(ieml::String("key"))};
	ASSERT_TRUE(elem.isDefined());
	ASSERT_EQ(&elem, &node[ieml::String("key")]);
	
	ASSERT_TRUE(elem.isNull());
	ASSERT_FALSE(elem.isRaw());
	ASSERT_FALSE(elem.isString());
	ASSERT_FALSE(elem.isList());
	ASSERT_FALSE(elem.isMap());
	ASSERT_FALSE(elem.isFile());
	ASSERT_FALSE(elem.isWithTag());
	ASSERT_FALSE(elem.isTakeAnchor());
	ASSERT_FALSE(elem.isGetAnchor());
	
	ieml::Node & incorrectElem{node.at(ieml::String("other-key"))};
	ASSERT_FALSE(incorrectElem.isDefined());
}

TEST(Node, Node_5_Tag) {
	ieml::Node node{ieml::TagData{ieml::NodeData{ieml::NullData{}}, ieml::Tag{"tag"}}};
	
	ASSERT_TRUE(node.isNull());
	ASSERT_FALSE(node.isRaw());
	ASSERT_FALSE(node.isString());
	ASSERT_FALSE(node.isList());
	ASSERT_FALSE(node.isMap());
	ASSERT_FALSE(node.isFile());
	ASSERT_TRUE(node.isWithTag());
	ASSERT_FALSE(node.isTakeAnchor());
	ASSERT_FALSE(node.isGetAnchor());
	
	ASSERT_EQ(node.getTag().some(), ieml::Tag{"tag"});
}

TEST(Node, Node_6_File) {
	ieml::Node node{ieml::NullData{}, ieml::FilePath{"file.ieml"}};
	
	ASSERT_TRUE(node.isNull());
	ASSERT_FALSE(node.isRaw());
	ASSERT_FALSE(node.isString());
	ASSERT_FALSE(node.isList());
	ASSERT_FALSE(node.isMap());
	ASSERT_TRUE(node.isFile());
	ASSERT_FALSE(node.isWithTag());
	ASSERT_FALSE(node.isTakeAnchor());
	ASSERT_FALSE(node.isGetAnchor());
	
	ASSERT_EQ(node.getFilePath().some(), ieml::FilePath{"file.ieml"});
}

TEST(Node, Node_7_TakeAnchor) {
	ieml::RcPtr<ieml::AnchorKeeper> anchorKeeper{std::make_shared<ieml::AnchorKeeper>()};
	anchorKeeper->add(ieml::String{"take_anchor"}, ieml::NodeData{ieml::NullData{}});
	ieml::Node node{ieml::TakeAnchorData{anchorKeeper, ieml::String{"take_anchor"}}};
	
	ASSERT_TRUE(node.isNull());
	ASSERT_FALSE(node.isRaw());
	ASSERT_FALSE(node.isString());
	ASSERT_FALSE(node.isList());
	ASSERT_FALSE(node.isMap());
	ASSERT_FALSE(node.isFile());
	ASSERT_FALSE(node.isWithTag());
	ASSERT_TRUE(node.isTakeAnchor());
	ASSERT_FALSE(node.isGetAnchor());
	
	ASSERT_EQ(node.getTakeAnchorName().some(), ieml::String{"take_anchor"});
	ASSERT_EQ(node.getAnchorName().some(), ieml::String{"take_anchor"});
}

TEST(Node, Node_8_GetAnchor) {
	ieml::RcPtr<ieml::AnchorKeeper> anchorKeeper{std::make_shared<ieml::AnchorKeeper>()};
	anchorKeeper->add(ieml::String{"get_anchor"}, ieml::NodeData{ieml::NullData{}});
	ieml::Node node{ieml::GetAnchorData{anchorKeeper, ieml::String{"get_anchor"}}};
	
	ASSERT_TRUE(node.isNull());
	ASSERT_FALSE(node.isRaw());
	ASSERT_FALSE(node.isString());
	ASSERT_FALSE(node.isList());
	ASSERT_FALSE(node.isMap());
	ASSERT_FALSE(node.isFile());
	ASSERT_FALSE(node.isWithTag());
	ASSERT_FALSE(node.isTakeAnchor());
	ASSERT_TRUE(node.isGetAnchor());
	
	ASSERT_EQ(node.getGetAnchorName().some(), ieml::String{"get_anchor"});
	ASSERT_EQ(node.getAnchorName().some(), ieml::String{"get_anchor"});
}