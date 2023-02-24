#pragma once

#include <map>
#include <vector>
#include <string>
#include <variant>
#include "../../fileSystem/fileSystem.hpp"
#include "../NodeType/NodeType.hpp"

namespace ieml {
	using llint = long long;
	
	class Node;
	
	using Tag = std::string;
	using FilePath = ieml::fs::path;
	
	/// @brief Node data storing null
	struct NullData {};
	
	/// @brief Node data storing the raw string
	struct RawData;
	
	/// @brief Node data storing scalar
	using StringData = std::string;
	
	/// @brief Node data storing a list of other nodes
	using ListData = std::vector<Node>;
	
	/// @brief Node data storing a map of named other nodes
	using MapData = std::map<std::string, Node>;
	
	/// @brief Node data storing tag and other data
	struct TagData;
	
	/// @brief Node data storing the file path and other data
	struct FileData;
	
	/// @brief Variant for storing different node data
	using NodeData = std::variant<NullData, RawData, StringData, ListData, MapData, TagData, FileData>;
	using PNodeData = NodeData*;
	
	struct RawData {
		std::string str;
		
		operator std::string() const;
	};
	
	struct TagData {
		PNodeData data;
		Tag tag;
		
		TagData(PNodeData data, Tag tag);
		
		TagData(const TagData& other);
		
		~TagData();
	};
	
	struct FileData {
		PNodeData data;
		FilePath filePath;
		
		FileData(PNodeData data, FilePath filePath);
		
		FileData(const FileData& other);
		
		~FileData();
	};
}
