#include <gtest/gtest.h>

#include <IEML/node/Node/Node.hpp>

static auto testFiles = absl::flat_hash_map<ieml::String , ieml::String>{
	std::make_pair(
		ieml::String{"test-1.ieml"},
		ieml::String{
			"null"
		}
	),
	std::make_pair(
		ieml::String{"test-2.ieml"},
		ieml::String{
			"*anchor"
		}
	)
};

struct TestFileInclude {
	static ieml::NodeData include(ieml::RcPtr<ieml::AnchorKeeper> anchorKeeper, ieml::FilePath filePath) {
		ieml::String inputStr{testFiles.at(filePath.string())};
		ieml::Parser parser{inputStr, anchorKeeper};
		return parser.parse();
	}
	
	static ieml::FilePath getFilePath(const ieml::FilePath&, ieml::FilePath&& filePath) {
		return filePath.concat(".ieml");
	}
};

TEST(parser, Parser_parseFile) {
	{
		ieml::String str{"< test-1"};
		ieml::BasicParser<ieml::Char, TestFileInclude> parser{str};
		auto file{parser.parseFile(2)};
		auto info{parser.getPosInfo()};
		ASSERT_TRUE(file.is_some());
		ASSERT_EQ(file.except().filePath_, ieml::FilePath{"test-1.ieml"});
		ASSERT_TRUE(file.except().node_->isNull());
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
		auto file{parser.parseFile(2)};
		ASSERT_TRUE(file.is_some());
		ASSERT_EQ(file.except().filePath_, ieml::String{"test-2.ieml"});
		ASSERT_TRUE(file.except().node_->isNull());
		
		auto anchor{file.except().node_->getGetAnchorName()};
		ASSERT_TRUE(anchor.is_some());
		ASSERT_EQ(anchor.except(), ieml::String{"anchor"});
		
		auto info{parser.getPosInfo()};
		ASSERT_EQ(info.pos, str.cbegin() + 23);
		ASSERT_EQ(info.mark.line, 1);
		ASSERT_EQ(info.mark.symbol, 14);
	}
	{
		ieml::String str{R"(< test-2)"};
		auto keeper{ieml::makeRcPtr<ieml::AnchorKeeper>()};
		keeper->add(ieml::String{"anchor"}, ieml::Node{ieml::NullData{}});
		ieml::BasicParser<ieml::Char, TestFileInclude> parser{str, keeper};
		auto file{parser.parseFile(2)};
		ASSERT_TRUE(file.is_some());
		ASSERT_EQ(file.except().filePath_, ieml::String{"test-2.ieml"});
		ASSERT_TRUE(file.except().node_->isNull());
		
		auto anchor{file.except().node_->getGetAnchorName()};
		ASSERT_TRUE(anchor.is_some());
		ASSERT_EQ(anchor.except(), ieml::String{"anchor"});
		
		auto info{parser.getPosInfo()};
		ASSERT_EQ(info.pos, str.cbegin() + 8);
		ASSERT_EQ(info.mark.line, 0);
		ASSERT_EQ(info.mark.symbol, 8);
	}
	{
		ieml::String str{R"(<test-1)"};
		ieml::BasicParser<ieml::Char, TestFileInclude> parser{str};
		auto file{parser.parseFile(2)};
		auto info{parser.getPosInfo()};
		ASSERT_FALSE(file.is_some());
		ASSERT_EQ(info.pos, str.cbegin() + 0);
		ASSERT_EQ(info.mark.line, 0);
		ASSERT_EQ(info.mark.symbol, 0);
	}
}