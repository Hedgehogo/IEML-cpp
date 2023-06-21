#include <gtest/gtest.h>

#include <IEML/node.hpp>

TEST(node, ListData) {
	ieml::ListData first{ieml::NullData{}, ieml::RawData{"hello"}, ieml::StringData{"hello"}};
	ieml::ListData second{ieml::NullData{}, ieml::RawData{"hello"}, ieml::StringData{"goodbye"}};
	ieml::ListData third{ieml::NullData{}, ieml::RawData{"hello"}, ieml::StringData{"hello"}, ieml::StringData{"hello"}};
	
	ASSERT_TRUE(first == first);
	ASSERT_FALSE(first == second);
	ASSERT_FALSE(first == third);
}

TEST(node, MapData) {
	ieml::MapData first{{"first", ieml::NullData{}}, {"second", ieml::RawData{"hello"}}, {"third", ieml::StringData{"hello"}}};
	ieml::MapData second{{"first", ieml::NullData{}}, {"third", ieml::StringData{"hello"}}, {"second", ieml::RawData{"hello"}}};
	ieml::MapData third{{"first", ieml::NullData{}}, {"second", ieml::RawData{"hello"}}, {"third", ieml::StringData{"goodbye"}}};
	ieml::MapData fourth{{"first", ieml::NullData{}}, {"second", ieml::RawData{"hello"}}, {"third", ieml::StringData{"hello"}}, {"fourth", ieml::StringData{"hello"}}};
	
	ASSERT_TRUE(first == first);
	ASSERT_TRUE(first == second);
	ASSERT_FALSE(first == third);
	ASSERT_FALSE(first == fourth);
}

TEST(node, FileData) {
	auto firstKeeper{ieml::makeRcPtr<ieml::AnchorKeeper>()};
	firstKeeper->add("first", ieml::NullData{});
	firstKeeper->addToFile("first-file", ieml::NullData{});
	auto secondKeeper{ieml::makeRcPtr<ieml::AnchorKeeper>()};
	secondKeeper->add("first", ieml::NullData{});
	secondKeeper->add("first-file", ieml::NullData{});
	
	ieml::FileData first{ieml::NullData{}, "test.ieml", firstKeeper};
	ieml::FileData second{ieml::RawData{"hello"}, "test.ieml", firstKeeper};
	ieml::FileData third{ieml::NullData{}, "test-2.ieml", firstKeeper};
	ieml::FileData fourth{ieml::NullData{}, "test.ieml", secondKeeper};
	
	ASSERT_TRUE(first == first);
	ASSERT_FALSE(first == second);
	ASSERT_FALSE(first == third);
	ASSERT_FALSE(first == fourth);
}