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
	auto first_keeper{ieml::make_rc_ptr<ieml::AnchorKeeper>()};
	first_keeper->add("first", ieml::NullData{});
	first_keeper->add_to_file("first-file", ieml::NullData{});
	auto second_keeper{ieml::make_rc_ptr<ieml::AnchorKeeper>()};
	second_keeper->add("first", ieml::NullData{});
	second_keeper->add("first-file", ieml::NullData{});
	
	ieml::FileData first{ieml::NullData{}, "test.ieml", first_keeper};
	ieml::FileData second{ieml::RawData{"hello"}, "test.ieml", first_keeper};
	ieml::FileData third{ieml::NullData{}, "test-2.ieml", first_keeper};
	ieml::FileData fourth{ieml::NullData{}, "test.ieml", second_keeper};
	
	ASSERT_TRUE(first == first);
	ASSERT_FALSE(first == second);
	ASSERT_FALSE(first == third);
	ASSERT_FALSE(first == fourth);
}