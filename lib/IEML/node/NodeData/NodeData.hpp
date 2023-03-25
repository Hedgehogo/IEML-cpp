#pragma once

#include <map>
#include <vector>
#include <string>
#include <variant>
#include <unordered_map>
#include "../../helpers/fileSystem/fileSystem.hpp"
#include "../NodeType/NodeType.hpp"

namespace ieml {
	using llint = long long;
	template<typename T>
	using Rc = std::shared_ptr<T>;
	template<typename T>
	using Weak = std::weak_ptr<T>;
	template<typename T>
	using Box = std::unique_ptr<T>;
	
	class Node;
	
	class PNode {
	public:
		using Ptr = Box<Node>;
		
	private:
		Ptr node;
		
	public:
		PNode(const Node& node);
		
		PNode(PNode&& other);
		
		PNode(const PNode& other);
		
		Node& operator*() const;
		
		Node* operator->() const;
		
		PNode& operator=(const PNode& other);
		
		operator const Ptr&() const;
		
		operator Ptr&();
	};
	
	
	using Tag = String;
	
	/// @brief Node data storing null
	struct NullData {};
	
	/// @brief Node data storing the raw string
	struct RawData;
	
	/// @brief Node data storing scalar
	using StringData = String;
	
	/// @brief Node data storing a list of other nodes
	using ListData = std::vector<Node>;
	
	/// @brief Node data storing a map of named other nodes
	using MapData = std::unordered_map<String, PNode>;
	
	/// @brief Node data storing tag and other data
	struct TagData;
	
	/// @brief Node data storing the file path and other data
	struct FileData;
	
	/// @brief Node data storing anchor
	struct TakeAnchorData;
	
	/// @brief Node data storing reference
	struct GetAnchorData;
	
	/// @brief Variant for storing different node data
	using NodeData = std::variant<NullData, RawData, StringData, ListData, MapData, TagData, FileData, TakeAnchorData, GetAnchorData>;
	
	struct RawData {
		String str;
		
		operator String() const;
	};
	
	struct TagData {
		Box<NodeData> data;
		Tag tag;
		
		TagData(Box<NodeData> data, const Tag& tag);
		
		TagData(const NodeData& data, const Tag& tag);
		
		TagData(const TagData& other);
		
		TagData& operator=(const TagData& other);
	};
	
	struct FileData {
		Box<NodeData> data;
		FilePath filePath;
		
		FileData(Box<NodeData> data, const FilePath& filePath);
		
		FileData(const NodeData& data, const FilePath& filePath);
		
		FileData(const FileData& other);
		
		FileData& operator=(const FileData& other);
	};
	
	class AnchorKeeper;
	
	struct TakeAnchorData {
		Rc<AnchorKeeper> keeper;
		String name;
	};
	
	struct GetAnchorData {
		Rc<AnchorKeeper> keeper;
		String name;
	};
}
