#include <gtest/gtest.h>

#include <IEML/parser.hpp>

static auto test_files = absl::flat_hash_map<ieml::String , ieml::String>{
	std::make_pair(
		ieml::String{"test-1.ieml"},
		ieml::String{
			"null"
		}
	),
	std::make_pair(
		ieml::String{"test-2.ieml"},
		ieml::String{
			"@anchor"
		}
	)
};

struct TestFileInclude {
	static ieml::NodeData include(ieml::RcPtr<ieml::AnchorKeeper> anchor_keeper, ieml::FilePath file_path) {
		ieml::String input_str{test_files.at(file_path.string())};
		ieml::Parser parser{input_str, anchor_keeper};
		return parser.parse();
	}
	
	static ieml::FilePath get_file_path(const ieml::FilePath&, ieml::FilePath&& file_path) {
		return file_path.concat(".ieml");
	}
};

TEST(parser, Parser_parse_file) {
	{
		ieml::String str{"< test-1"};
		ieml::BasicParser<ieml::Char, TestFileInclude> parser{str};
		auto file{parser.parse_file(2)};
		auto info{parser.get_pos_info()};
		ASSERT_TRUE(file.is_some());
		ASSERT_EQ(file.except().file_path_, ieml::FilePath{"test-1.ieml"});
		ASSERT_TRUE(file.except().node_->is_null());
		ASSERT_EQ(info.pos, str.cbegin() + 8);
		ASSERT_EQ(info.mark.line, 0);
		ASSERT_EQ(info.mark.symbol, 8);
	}
	{
		ieml::String str{
			R"(< test-2
		anchor: null)"
		};
		ieml::BasicParser<ieml::Char, TestFileInclude> parser{str};
		auto file{parser.parse_file(2)};
		ASSERT_TRUE(file.is_some());
		ASSERT_EQ(file.except().file_path_, ieml::String{"test-2.ieml"});
		ASSERT_TRUE(file.except().node_->is_null());
		
		auto anchor{file.except().node_->get_get_anchor_name()};
		ASSERT_TRUE(anchor.is_some());
		ASSERT_EQ(anchor.except(), ieml::String{"anchor"});
		
		auto info{parser.get_pos_info()};
		ASSERT_EQ(info.pos, str.cbegin() + 23);
		ASSERT_EQ(info.mark.line, 1);
		ASSERT_EQ(info.mark.symbol, 14);
	}
	{
		ieml::String str{R"(< test-2)"};
		auto keeper{ieml::make_rc_ptr<ieml::AnchorKeeper>()};
		keeper->add(ieml::String{"anchor"}, ieml::Node{ieml::NullData{}});
		ieml::BasicParser<ieml::Char, TestFileInclude> parser{str, keeper};
		auto file{parser.parse_file(2)};
		ASSERT_TRUE(file.is_some());
		ASSERT_EQ(file.except().file_path_, ieml::String{"test-2.ieml"});
		ASSERT_TRUE(file.except().node_->is_null());
		
		auto anchor{file.except().node_->get_get_anchor_name()};
		ASSERT_TRUE(anchor.is_some());
		ASSERT_EQ(anchor.except(), ieml::String{"anchor"});
		
		auto info{parser.get_pos_info()};
		ASSERT_EQ(info.pos, str.cbegin() + 8);
		ASSERT_EQ(info.mark.line, 0);
		ASSERT_EQ(info.mark.symbol, 8);
	}
	{
		ieml::String str{R"(<test-1)"};
		ieml::BasicParser<ieml::Char, TestFileInclude> parser{str};
		auto file{parser.parse_file(2)};
		auto info{parser.get_pos_info()};
		ASSERT_FALSE(file.is_some());
		ASSERT_EQ(info.pos, str.cbegin() + 0);
		ASSERT_EQ(info.mark.line, 0);
		ASSERT_EQ(info.mark.symbol, 0);
	}
}