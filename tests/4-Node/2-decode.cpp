#include <gtest/gtest.h>

#include <IEML/node/Node/Node.hpp>

TEST(Node, decode_int) {
	ieml::Node node{ieml::RawData{"-8_246"}};
	ASSERT_EQ(node.as<int>(), -8246);
	ASSERT_EQ(node.as<float>(), -8246.f);
	
	ieml::Node node_basis{ieml::RawData{"16'FF"}};
	ASSERT_FLOAT_EQ(node_basis.as<int>(), 255);
	ASSERT_FLOAT_EQ(node_basis.as<float>(), 255.f);
}

TEST(Node, decode_float) {
	ieml::Node node{ieml::RawData{"-8_246.73"}};
	ASSERT_FLOAT_EQ(node.as<float>(), -8246.73f);
	
	ieml::Node node_basis{ieml::RawData{"3'0.1"}};
	ASSERT_FLOAT_EQ(node_basis.as<float>(), 1.f/3.f);
}

TEST(Node, decode_string) {
	ieml::Node node{ieml::StringData{"Some\n string"}};
	ASSERT_EQ(node.as<ieml::String>(), ieml::String{"Some\n string"});
}

TEST(Node, decode_raw) {
	ieml::Node node{ieml::RawData{"Some\n string"}};
	ASSERT_EQ(node.as<ieml::RawData>().str, ieml::RawData{"Some\n string"}.str);
}

TEST(Node, decode_list) {
	ieml::Node node{ieml::ListData{ieml::Node{ieml::NullData{}}, ieml::Node{ieml::RawData{""}}}};
	const ieml::ListData& list{node.as<ieml::ListData>()};
	
	EXPECT_NO_THROW(list.at(0));
	ASSERT_TRUE(list.at(0).isNull());
	EXPECT_NO_THROW(list.at(1));
	ASSERT_TRUE(list.at(1).isRaw());
	EXPECT_ANY_THROW(list.at(2));
}

TEST(Node, decode_map) {
	ieml::Node node {
		ieml::MapData {
			{
				ieml::String{"first"},
				ieml::PNode{ieml::Node{ieml::NullData{}}}
			}, {
				ieml::String{"second"},
				ieml::PNode{ieml::Node{ieml::RawData{""}}}
			}
		}
	};
	const ieml::MapData& map{node.as<ieml::MapData>()};
	
	EXPECT_NO_THROW(map.at(ieml::String{"first"}));
	ASSERT_TRUE(map.at(ieml::String{"first"})->isNull());
	EXPECT_NO_THROW(map.at(ieml::String{"second"}));
	ASSERT_TRUE(map.at(ieml::String{"second"})->isRaw());
	EXPECT_ANY_THROW(map.at(ieml::String{"other-key"}));
}
