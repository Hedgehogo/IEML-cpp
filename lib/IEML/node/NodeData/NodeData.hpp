#pragma once

#include <map>
#include <vector>
#include <string>
#include <variant>
#include <unordered_map>
#include "../../helpers/fileSystem/fileSystem.hpp"
#include "../../helpers/pointers/pointers.hpp"
#include "../NodeType/NodeType.hpp"

namespace ieml {
	using llint = long long;
	
	template<typename Char_>
	class BasicNode;
	
	template<typename Char_>
	struct BasicNodeData;
	
	/// @brief Node data storing null
	struct NullData {};
	
	/// @brief Node data storing the raw string
	template<typename Char_>
	struct BasicRawData {
		BasicString<Char_> str;
		
		operator BasicString<Char_>() const;
	};
	
	using RawData = BasicRawData<Char>;
	
	/// @brief Node data storing scalar
	template<typename Char_>
	using BasicStringData = BasicString<Char_>;
	
	using StringData = BasicStringData<Char>;
	
	/// @brief Node data storing a list of other nodes
	template<typename Char_>
	using BasicListData = std::vector<BasicNode<Char_>>;
	
	using ListData = BasicListData<Char>;
	
	/// @brief Node data storing a map of named other nodes
	template<typename Char_>
	using BasicMapData = std::unordered_map<BasicString<Char_>, BasicNode<Char_>>;
	
	using MapData = BasicMapData<Char>;
	
	template<typename Char_>
	using BasicTag = BasicString<Char_>;
	
	using Tag = BasicTag<Char>;
	
	/// @brief Node data storing tag and other data
	template<typename Char_>
	struct BasicTagData {
		Box<BasicNodeData<Char_>> data;
		BasicTag<Char_> tag;
		
		BasicTagData(Box<BasicNodeData<Char_>> data, const BasicTag<Char_>& tag);
		
		BasicTagData(const BasicNodeData<Char_>& data, const BasicTag<Char_>& tag);
		
		BasicTagData(const BasicTagData& other);
		
		BasicTagData& operator=(const BasicTagData& other);
	};
	
	using TagData = BasicTagData<Char>;
	
	/// @brief Node data storing the file path and other data
	template<typename Char_>
	struct BasicFileData {
		Box<BasicNodeData<Char_>> data;
		FilePath filePath;
		
		BasicFileData(Box<BasicNodeData<Char_>> data, const FilePath& filePath);
		
		BasicFileData(const BasicNodeData<Char_>& data, const FilePath& filePath);
		
		BasicFileData(const BasicFileData& other);
		
		BasicFileData& operator=(const BasicFileData& other);
	};
	
	using FileData = BasicFileData<Char>;
	
	template<typename Char_>
	class BasicAnchorKeeper;
	
	/// @brief Node data storing anchor
	template<typename Char_>
	struct BasicTakeAnchorData {
		Rc<BasicAnchorKeeper<Char_>> keeper;
		String name;
	};
	
	using TakeAnchorData = BasicTakeAnchorData<Char>;
	
	/// @brief Node data storing reference
	template<typename Char_>
	struct BasicGetAnchorData {
		Rc<BasicAnchorKeeper<Char_>> keeper;
		String name;
	};
	
	using GetAnchorData = BasicGetAnchorData<Char>;
	
	/// @brief Variant for storing different node data
	template<typename Char_>
	struct BasicNodeData {
		std::variant<
			NullData,
			BasicRawData<Char_>,
			BasicStringData<Char_>,
			BasicListData<Char_>,
			BasicMapData<Char_>,
			BasicTagData<Char_>,
			BasicFileData<Char_>,
			BasicTakeAnchorData<Char_>,
			BasicGetAnchorData<Char_>
		> data;
	};
	
	using NodeData = BasicNodeData<Char>;
}
