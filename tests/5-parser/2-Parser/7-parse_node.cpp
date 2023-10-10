#include <gtest/gtest.h>

#include <IEML/parser.hpp>

struct TestInclude {
	static ieml::NodeData include(ieml::RcPtr<ieml::AnchorKeeper> anchor_keeper, ieml::FilePath file_path) {
		return {ieml::NullData{}};
	}
	
	static ieml::FilePath get_file_path(const ieml::FilePath&, ieml::FilePath&& new_file_path) {
		return new_file_path.concat(".ieml");
	}
};

TEST(parser, Parser_parse_node) {
	{
		ieml::String str{R"(null)"};
		ieml::Parser parser{str};
		auto node{parser.parse_node(2)};
		auto info{parser.get_pos_info()};
		ASSERT_EQ(node.data_.index(), 0);
		ASSERT_EQ(info.pos, str.cbegin() + 4);
		ASSERT_EQ(info.mark.line, 0);
		ASSERT_EQ(info.mark.symbol, 4);
	}
	{
		ieml::String str{
			R"( # hello
		null)"
		};
		ieml::Parser parser{str};
		auto node{parser.parse_node(2)};
		auto info{parser.get_pos_info()};
		ASSERT_EQ(node.data_.index(), 0);
		ASSERT_EQ(info.pos, str.cbegin() + 15);
		ASSERT_EQ(info.mark.line, 1);
		ASSERT_EQ(info.mark.symbol, 6);
	}
	{
		ieml::String str{R"(hello)"};
		ieml::Parser parser{str};
		auto node{parser.parse_node(2)};
		auto info{parser.get_pos_info()};
		ASSERT_EQ(node.data_.index(), 1);
		ASSERT_EQ(std::get<1>(node.data_).str, ieml::String{"hello"});
		ASSERT_EQ(info.pos, str.cbegin() + 5);
		ASSERT_EQ(info.mark.line, 0);
		ASSERT_EQ(info.mark.symbol, 5);
	}
	{
		ieml::String str{R"(> hello)"};
		ieml::Parser parser{str};
		auto node{parser.parse_node(2)};
		auto info{parser.get_pos_info()};
		ASSERT_EQ(node.data_.index(), 2);
		ASSERT_EQ(std::get<2>(node.data_), ieml::String{"hello"});
		ASSERT_EQ(info.pos, str.cbegin() + 7);
		ASSERT_EQ(info.mark.line, 0);
		ASSERT_EQ(info.mark.symbol, 7);
	}
	{
		ieml::String str{
			R"(>> # hello
		hello)"
		};
		ieml::Parser parser{str};
		auto node{parser.parse_node(2)};
		auto info{parser.get_pos_info()};
		ASSERT_EQ(node.data_.index(), 2);
		ASSERT_EQ(std::get<2>(node.data_), ieml::String{"hello"});
		ASSERT_EQ(info.pos, str.cbegin() + 18);
		ASSERT_EQ(info.mark.line, 1);
		ASSERT_EQ(info.mark.symbol, 7);
	}
	{
		ieml::String str{R"("hello" # hello)"};
		ieml::Parser parser{str};
		auto node{parser.parse_node(2)};
		auto info{parser.get_pos_info()};
		ASSERT_EQ(node.data_.index(), 2);
		ASSERT_EQ(std::get<2>(node.data_), ieml::String{"hello"});
		ASSERT_EQ(info.pos, str.cbegin() + 15);
		ASSERT_EQ(info.mark.line, 0);
		ASSERT_EQ(info.mark.symbol, 15);
	}
	{
		ieml::String str{
			R"(- null
		- null)"
		};
		ieml::Parser parser{str};
		auto node{parser.parse_node(2)};
		auto info{parser.get_pos_info()};
		ASSERT_EQ(node.data_.index(), 3);
		ASSERT_EQ(std::get<3>(node.data_).size(), 2);
		ASSERT_EQ(info.pos, str.cbegin() + 15);
		ASSERT_EQ(info.mark.line, 1);
		ASSERT_EQ(info.mark.symbol, 8);
	}
	{
		ieml::String str{
			R"(first: null
		second: null)"
		};
		ieml::Parser parser{str};
		auto node{parser.parse_node(2)};
		auto info{parser.get_pos_info()};
		ASSERT_EQ(node.data_.index(), 4);
		ASSERT_EQ(std::get<4>(node.data_).size(), 2);
		ASSERT_EQ(info.pos, str.cbegin() + 26);
		ASSERT_EQ(info.mark.line, 1);
		ASSERT_EQ(info.mark.symbol, 14);
	}
	{
		ieml::String str{R"(= Tag: null)"};
		ieml::Parser parser{str};
		auto node{parser.parse_node(2)};
		auto info{parser.get_pos_info()};
		ASSERT_EQ(node.data_.index(), 5);
		ASSERT_EQ(std::get<5>(node.data_).tag_, ieml::String{"Tag"});
		ASSERT_EQ(info.pos, str.cbegin() + 11);
		ASSERT_EQ(info.mark.line, 0);
		ASSERT_EQ(info.mark.symbol, 11);
	}
	{
		ieml::String str{R"(< test)"};
		ieml::BasicParser<ieml::Char, TestInclude> parser{str};
		auto node{parser.parse_node(2)};
		auto info{parser.get_pos_info()};
		ASSERT_EQ(node.data_.index(), 6);
		ASSERT_EQ(std::get<6>(node.data_).file_path_, ieml::FilePath{"test.ieml"});
		ASSERT_EQ(info.pos, str.cbegin() + 6);
		ASSERT_EQ(info.mark.line, 0);
		ASSERT_EQ(info.mark.symbol, 6);
	}
	{
		ieml::String str{R"(&anchor null)"};
		ieml::Parser parser{str};
		auto node{parser.parse_node(2)};
		auto info{parser.get_pos_info()};
		ASSERT_EQ(node.data_.index(), 7);
		ASSERT_EQ(std::get<7>(node.data_).name_, ieml::String{"anchor"});
		ASSERT_EQ(info.pos, str.cbegin() + 12);
		ASSERT_EQ(info.mark.line, 0);
		ASSERT_EQ(info.mark.symbol, 12);
	}
	{
		ieml::String str{R"(*anchor)"};
		ieml::Parser parser{str};
		auto node{parser.parse_node(2)};
		auto info{parser.get_pos_info()};
		ASSERT_EQ(node.data_.index(), 8);
		ASSERT_EQ(std::get<8>(node.data_).name_, ieml::String{"anchor"});
		ASSERT_EQ(info.pos, str.cbegin() + 7);
		ASSERT_EQ(info.mark.line, 0);
		ASSERT_EQ(info.mark.symbol, 7);
	}
}