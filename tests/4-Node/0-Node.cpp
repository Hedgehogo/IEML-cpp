#include <gtest/gtest.h>

#include <IEML/parser.hpp>

TEST(Node, Node_0_Null) {
	ieml::Node node{ieml::NullData{}, ieml::Mark{2, 5}};
	ASSERT_EQ(node.get_mark().line, 2);
	ASSERT_EQ(node.get_mark().symbol, 5);
	
	ASSERT_TRUE(node.is_null());
	ASSERT_FALSE(node.is_raw());
	ASSERT_FALSE(node.is_string());
	ASSERT_FALSE(node.is_list());
	ASSERT_FALSE(node.is_map());
	ASSERT_FALSE(node.is_file());
	ASSERT_FALSE(node.is_with_tag());
	ASSERT_FALSE(node.is_take_anchor());
	ASSERT_FALSE(node.is_get_anchor());
}

TEST(Node, Node_1_Raw) {
	ieml::Node node{ieml::RawData{}};
	
	ASSERT_FALSE(node.is_null());
	ASSERT_TRUE(node.is_raw());
	ASSERT_FALSE(node.is_string());
	ASSERT_FALSE(node.is_list());
	ASSERT_FALSE(node.is_map());
	ASSERT_FALSE(node.is_file());
	ASSERT_FALSE(node.is_with_tag());
	ASSERT_FALSE(node.is_take_anchor());
	ASSERT_FALSE(node.is_get_anchor());
}

TEST(Node, Node_2_String) {
	ieml::Node node{ieml::StringData{}};
	
	ASSERT_FALSE(node.is_null());
	ASSERT_FALSE(node.is_raw());
	ASSERT_TRUE(node.is_string());
	ASSERT_FALSE(node.is_list());
	ASSERT_FALSE(node.is_map());
	ASSERT_FALSE(node.is_file());
	ASSERT_FALSE(node.is_with_tag());
	ASSERT_FALSE(node.is_take_anchor());
	ASSERT_FALSE(node.is_get_anchor());
}

TEST(Node, Node_3_List) {
	ieml::Node node{ieml::ListData{ieml::Node{ieml::NullData{}}}};
	
	ASSERT_FALSE(node.is_null());
	ASSERT_FALSE(node.is_raw());
	ASSERT_FALSE(node.is_string());
	ASSERT_TRUE(node.is_list());
	ASSERT_FALSE(node.is_map());
	ASSERT_FALSE(node.is_file());
	ASSERT_FALSE(node.is_with_tag());
	ASSERT_FALSE(node.is_take_anchor());
	ASSERT_FALSE(node.is_get_anchor());
	
	ASSERT_EQ(node.get_list_size().except(), 1);
	ASSERT_EQ(node.get_size().except(), 1);
	
	auto item{node.at(0)};
	ASSERT_TRUE(item.is_ok());
	ASSERT_EQ(&item.ok(), &node[0].except());
	
	ASSERT_TRUE(item.ok().is_null());
	ASSERT_FALSE(item.ok().is_raw());
	ASSERT_FALSE(item.ok().is_string());
	ASSERT_FALSE(item.ok().is_list());
	ASSERT_FALSE(item.ok().is_map());
	ASSERT_FALSE(item.ok().is_file());
	ASSERT_FALSE(item.ok().is_with_tag());
	ASSERT_FALSE(item.ok().is_take_anchor());
	ASSERT_FALSE(item.ok().is_get_anchor());
	
	auto incorrect_item{node.at(1)};
	ASSERT_FALSE(incorrect_item.is_ok());
	
	auto view{node.get_list_view()};
	ASSERT_TRUE(view.is_ok());
	ASSERT_EQ(view.ok().get_size(), 1);
	ASSERT_EQ(&view.ok().get_list(), &node.get_list().except());
	
	auto view_item{view.ok().at(0)};
	ASSERT_TRUE(view_item.is_ok());
	ASSERT_EQ(&view_item.ok(), &(view.ok()[0].except()));
	ASSERT_EQ(&view_item.ok(), &item.ok());
	
	auto incorrect_view_item{view.ok().at(1)};
	ASSERT_FALSE(incorrect_view_item.is_ok());
}

TEST(Node, Node_4_Map) {
	ieml::Node node{ieml::MapData{{ieml::String{"key"}, ieml::Node{ieml::NullData{}}}}};
	
	ASSERT_FALSE(node.is_null());
	ASSERT_FALSE(node.is_raw());
	ASSERT_FALSE(node.is_string());
	ASSERT_FALSE(node.is_list());
	ASSERT_TRUE(node.is_map());
	ASSERT_FALSE(node.is_file());
	ASSERT_FALSE(node.is_with_tag());
	ASSERT_FALSE(node.is_take_anchor());
	ASSERT_FALSE(node.is_get_anchor());
	
	ASSERT_EQ(node.get_map_size().except(), 1);
	ASSERT_EQ(node.get_size().except(), 1);
	
	auto item{node.at(ieml::String("key"))};
	ASSERT_TRUE(item.is_ok());
	ASSERT_EQ(&item.ok(), &node[ieml::String("key")].ok());
	
	ASSERT_TRUE(item.ok().is_null());
	ASSERT_FALSE(item.ok().is_raw());
	ASSERT_FALSE(item.ok().is_string());
	ASSERT_FALSE(item.ok().is_list());
	ASSERT_FALSE(item.ok().is_map());
	ASSERT_FALSE(item.ok().is_file());
	ASSERT_FALSE(item.ok().is_with_tag());
	ASSERT_FALSE(item.ok().is_take_anchor());
	ASSERT_FALSE(item.ok().is_get_anchor());
	
	auto incorrect_item{node.at(ieml::String("other-key"))};
	ASSERT_FALSE(incorrect_item.is_ok());
	
	auto view{node.get_map_view()};
	ASSERT_TRUE(view.is_ok());
	ASSERT_EQ(view.ok().get_size(), 1);
	ASSERT_EQ(&view.ok().get_map(), &node.get_map().except());
	
	auto view_item{view.ok().at(ieml::String("key"))};
	ASSERT_TRUE(view_item.is_ok());
	ASSERT_EQ(&view_item.ok(), &(view.ok()[ieml::String("key")].except()));
	ASSERT_EQ(&view_item.ok(), &item.ok());
	
	auto incorrect_view_item{view.ok().at(ieml::String("other-key"))};
	ASSERT_FALSE(incorrect_view_item.is_ok());
}

TEST(Node, Node_5_Tag) {
	ieml::Node node{ieml::TagData{ieml::NodeData{ieml::NullData{}}, ieml::Tag{"tag"}}};
	
	ASSERT_TRUE(node.is_null());
	ASSERT_FALSE(node.is_raw());
	ASSERT_FALSE(node.is_string());
	ASSERT_FALSE(node.is_list());
	ASSERT_FALSE(node.is_map());
	ASSERT_FALSE(node.is_file());
	ASSERT_TRUE(node.is_with_tag());
	ASSERT_FALSE(node.is_take_anchor());
	ASSERT_FALSE(node.is_get_anchor());
	
	ASSERT_EQ(node.get_tag().some(), ieml::Tag{"tag"});
}

TEST(Node, Node_6_File) {
	auto anchor_keeper{std::make_shared<ieml::AnchorKeeper>()};
	ieml::Node node{ieml::FileData{ieml::NullData{}, ieml::FilePath{"file.ieml"}, anchor_keeper}};
	
	ASSERT_TRUE(node.is_null());
	ASSERT_FALSE(node.is_raw());
	ASSERT_FALSE(node.is_string());
	ASSERT_FALSE(node.is_list());
	ASSERT_FALSE(node.is_map());
	ASSERT_TRUE(node.is_file());
	ASSERT_FALSE(node.is_with_tag());
	ASSERT_FALSE(node.is_take_anchor());
	ASSERT_FALSE(node.is_get_anchor());
	
	ASSERT_EQ(node.get_file_path().some(), ieml::FilePath{"file.ieml"});
}

TEST(Node, Node_7_TakeAnchor) {
	ieml::RcPtr<ieml::AnchorKeeper> anchor_keeper{std::make_shared<ieml::AnchorKeeper>()};
	anchor_keeper->add(ieml::String{"take_anchor"}, ieml::NodeData{ieml::NullData{}});
	ieml::Node node{ieml::TakeAnchorData{anchor_keeper, ieml::String{"take_anchor"}}};
	
	ASSERT_TRUE(node.is_null());
	ASSERT_FALSE(node.is_raw());
	ASSERT_FALSE(node.is_string());
	ASSERT_FALSE(node.is_list());
	ASSERT_FALSE(node.is_map());
	ASSERT_FALSE(node.is_file());
	ASSERT_FALSE(node.is_with_tag());
	ASSERT_TRUE(node.is_take_anchor());
	ASSERT_FALSE(node.is_get_anchor());
	
	ASSERT_EQ(node.get_take_anchor_name().some(), ieml::String{"take_anchor"});
	ASSERT_EQ(node.get_anchor_name().some(), ieml::String{"take_anchor"});
}

TEST(Node, Node_8_GetAnchor) {
	ieml::RcPtr<ieml::AnchorKeeper> anchor_keeper{std::make_shared<ieml::AnchorKeeper>()};
	anchor_keeper->add(ieml::String{"get_anchor"}, ieml::NodeData{ieml::NullData{}});
	ieml::Node node{ieml::GetAnchorData{anchor_keeper, ieml::String{"get_anchor"}}};
	
	ASSERT_TRUE(node.is_null());
	ASSERT_FALSE(node.is_raw());
	ASSERT_FALSE(node.is_string());
	ASSERT_FALSE(node.is_list());
	ASSERT_FALSE(node.is_map());
	ASSERT_FALSE(node.is_file());
	ASSERT_FALSE(node.is_with_tag());
	ASSERT_FALSE(node.is_take_anchor());
	ASSERT_TRUE(node.is_get_anchor());
	
	ASSERT_EQ(node.get_get_anchor_name().some(), ieml::String{"get_anchor"});
	ASSERT_EQ(node.get_anchor_name().some(), ieml::String{"get_anchor"});
}

TEST(Node, Node_9_Equal) {
	ieml::Node first{ieml::RawData{"hello"}};
	ieml::Node second{ieml::RawData{"goodbye"}};
	ieml::Node third{ieml::ListData{ieml::StringData{"hello"}, ieml::NullData{}}};
	
	ASSERT_TRUE(first == first);
	ASSERT_FALSE(first == second);
	ASSERT_FALSE(first == third);
}