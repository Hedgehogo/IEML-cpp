#include <gtest/gtest.h>

#include <IEML/parser.hpp>

TEST(Node, decode_int) {
	ieml::Node node{ieml::RawData{"-8_246"}};
	ASSERT_EQ(node.as<int>().except(), -8246);
	ASSERT_EQ(node.as<float>().except(), -8246.f);
	
	ieml::Node node_basis{ieml::RawData{"16'FF"}};
	ASSERT_FLOAT_EQ(node_basis.as<int>().except(), 255);
	ASSERT_FLOAT_EQ(node_basis.as<float>().except(), 255.f);
	
	ieml::Node node_basis_comment{ieml::RawData{"16'FF # hello"}};
	ASSERT_FLOAT_EQ(node_basis_comment.as<int>().except(), 255);
	ASSERT_FLOAT_EQ(node_basis_comment.as<float>().except(), 255.f);
}

TEST(Node, decode_float) {
	ieml::Node node{ieml::RawData{"-8_246.73"}};
	ASSERT_FLOAT_EQ(node.as<float>().except(), -8246.73f);
	
	ieml::Node node_basis{ieml::RawData{"3'0.1"}};
	ASSERT_FLOAT_EQ(node_basis.as<float>().except(), 1.f/3.f);
	
	ieml::Node node_basis_comment{ieml::RawData{"3'0.1 # hello"}};
	ASSERT_FLOAT_EQ(node_basis_comment.as<float>().except(), 1.f/3.f);
}

TEST(Node, decode_bool) {
	ieml::Node node{ieml::RawData{"yes"}};
	ASSERT_FLOAT_EQ(node.as<bool>().except(), true);
	
	ieml::Node node_comment{ieml::RawData{"no # hello"}};
	ASSERT_FLOAT_EQ(node_comment.as<bool>().except(), false);
}

TEST(Node, decode_string) {
	ieml::Node node{ieml::StringData{"Some\n string"}};
	ASSERT_EQ(node.as<ieml::String>().except(), ieml::String{"Some\n string"});
}

TEST(Node, decode_raw) {
	ieml::Node node{ieml::RawData{"Some\n string"}};
	ASSERT_EQ(node.as<ieml::RawData>().except().str, ieml::RawData{"Some\n string"}.str);
}

TEST(Node, decode_list) {
	ieml::Node node{ieml::ListData{ieml::Node{ieml::NullData{}}, ieml::Node{ieml::RawData{""}}}};
	auto opt_list{node.as<ieml::ListData>()};
	auto& list{opt_list.except()};
	
	EXPECT_NO_THROW(list.at(0));
	ASSERT_TRUE(list.at(0).is_null());
	EXPECT_NO_THROW(list.at(1));
	ASSERT_TRUE(list.at(1).is_raw());
	EXPECT_ANY_THROW(list.at(2));
}

TEST(Node, decode_map) {
	ieml::Node node {
		ieml::MapData {
			{
				ieml::String{"first"},
				ieml::Node{ieml::NullData{}}
			}, {
				ieml::String{"second"},
				ieml::Node{ieml::RawData{""}}
			}
		}
	};
	auto map{node.as<ieml::MapData>().except()};
	
	EXPECT_NO_THROW(map.at(ieml::String{"first"}));
	ASSERT_TRUE(map.at(ieml::String{"first"}).is_null());
	EXPECT_NO_THROW(map.at(ieml::String{"second"}));
	ASSERT_TRUE(map.at(ieml::String{"second"}).is_raw());
	EXPECT_ANY_THROW(map.at(ieml::String{"other-key"}));
}

struct Vec2 {
	float x;
	float y;
};

template<typename Char_>
struct ieml::Decode<Char_, Vec2> {
	static ieml::Option<Vec2> decode(const ieml::Node& node) {
		return {Vec2{
			node.get_as<float>("x").except(),
			node.get_as<float>("y").except(),
		}};
	}
};

struct Rect {
	Vec2 position;
	Vec2 size;
};

template<typename Char_>
struct ieml::Decode<Char_, Rect> {
	static ieml::Option<Rect> decode(const ieml::Node& node) {
		return {Rect{
			node.get_as<Vec2>("position").except(),
			node.get_as<Vec2>("size").except(),
		}};
	}
};

TEST(Node, decode_custom_ok) {
	ieml::Node node {
		ieml::MapData {
			{
				ieml::String{"x"},
				ieml::Node{ieml::RawData{"15.7"}}
			}, {
				ieml::String{"y"},
				ieml::Node{ieml::RawData{"-94.1"}}
			}
		}
	};
	auto vec2{node.as<Vec2>()};
	
	ASSERT_TRUE(vec2.is_ok());
	ASSERT_FLOAT_EQ(vec2.except().x, 15.7);
	ASSERT_FLOAT_EQ(vec2.except().y, -94.1);
}

TEST(Node, decode_custom_error_1) {
	ieml::Node node {
		ieml::MapData {
			{
				ieml::String{"x"},
				ieml::Node{ieml::RawData{"15.7"}}
			}
		}
	};
	auto vec2{node.as<Vec2>()};
	
	ASSERT_FALSE(vec2.is_ok());
	ASSERT_TRUE(vec2.error().has_reason());
	ASSERT_EQ(vec2.error().get_type_name(), "Vec2");
	ASSERT_EQ(vec2.error().get_full_description(), "0:0: Failed to convert node to 'Vec2', because: \n0:0: A key named 'y' does not exist in the map.");
}

TEST(Node, decode_custom_error_2) {
	ieml::Node node {
		ieml::MapData {
			{
				ieml::String{"position"},
				ieml::Node{
					ieml::MapData {
						{
							ieml::String{"x"},
							ieml::Node{ieml::RawData{"15.7"}}
						}
					}
				}
			}
		}
	};
	auto rect{node.as<Rect>()};
	
	ASSERT_FALSE(rect.is_ok());
	ASSERT_TRUE(rect.error().has_reason());
	ASSERT_EQ(rect.error().get_type_name(), "Rect");
	ASSERT_EQ(rect.error().get_full_description(), "0:0: Failed to convert node to 'Rect', because: \n0:0: Failed to convert node to 'Vec2', because: \n0:0: A key named 'y' does not exist in the map.");
}
