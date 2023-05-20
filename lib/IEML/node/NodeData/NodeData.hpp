#pragma once

#include <map>
#include <vector>
#include <string>
#include <variant>
#include <absl/container/flat_hash_map.h>
#include "../../helpers/fileSystem/fileSystem.hpp"
#include "../../helpers/pointers/pointers.hpp"
#include "../../helpers/MetaFn/MetaFn.hpp"
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
	using BasicMapData = absl::flat_hash_map<BasicString<Char_>, BasicNode<Char_>>;
	
	using MapData = BasicMapData<Char>;
	
	template<typename Char_>
	using BasicTag = BasicString<Char_>;
	
	using Tag = BasicTag<Char>;
	
	template<typename Char_>
	struct BaseMetaData {
		BasicNode<Char_>* node_;
		
		BaseMetaData(BasicNode<Char_>&& node);
		
		BaseMetaData(const BasicNode<Char_>& node);
		
		BaseMetaData(BaseMetaData<Char_>&& other);
		
		BaseMetaData(const BaseMetaData<Char_>& other);
		
		~BaseMetaData();
		
		BaseMetaData<Char_>& operator=(const BaseMetaData<Char_>& other);
	};
	
	/// @brief Node data storing tag and other data
	template<typename Char_>
	struct BasicTagData : public BaseMetaData<Char_> {
		BasicTag<Char_> tag_;
		
		BasicTagData(BasicNode<Char_>&& node, const BasicTag<Char_>& tag);
		
		BasicTagData(const BasicNode<Char_>& node, const BasicTag<Char_>& tag);
	};
	
	using TagData = BasicTagData<Char>;
	
	/// @brief Node data storing the file path and other data
	template<typename Char_>
	struct BasicFileData : public BaseMetaData<Char_> {
		FilePath filePath_;
		
		BasicFileData(BasicNode<Char_>&& node, const FilePath& filePath);
		
		BasicFileData(const BasicNode<Char_>& node, const FilePath& filePath);
	};
	
	using FileData = BasicFileData<Char>;
	
	template<typename Char_>
	class BasicAnchorKeeper;
	
	template<typename Char_>
	struct BaseAnchorData {
		RcPtr<BasicAnchorKeeper<Char_>> keeper_;
		BasicString<Char_> name_;
	};
	
	/// @brief Node data storing anchor
	template<typename Char_>
	struct BasicTakeAnchorData : public BaseAnchorData<Char_> {};
	
	using TakeAnchorData = BasicTakeAnchorData<Char>;
	
	/// @brief Node data storing reference
	template<typename Char_>
	struct BasicGetAnchorData : public BaseAnchorData<Char_> {};
	
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
		> data_;
	};
	
	using NodeData = BasicNodeData<Char>;
	
	namespace detail {
		template<NodeType Type, typename Char_>
		struct ToNodeData;
		template<typename Char_>
		struct ToNodeData<NodeType::Null, Char_> : MetaFn<NullData> {};
		template<typename Char_>
		struct ToNodeData<NodeType::Raw, Char_> : MetaFn<BasicRawData<Char_>> {};
		template<typename Char_>
		struct ToNodeData<NodeType::String, Char_> : MetaFn<BasicStringData<Char_>> {};
		template<typename Char_>
		struct ToNodeData<NodeType::List, Char_> : MetaFn<BasicListData<Char_>> {};
		template<typename Char_>
		struct ToNodeData<NodeType::Map, Char_> : MetaFn<BasicMapData<Char_>> {};
		template<typename Char_>
		struct ToNodeData<NodeType::Tag, Char_> : MetaFn<BasicTagData<Char_>> {};
		template<typename Char_>
		struct ToNodeData<NodeType::File, Char_> : MetaFn<BasicFileData<Char_>> {};
		template<typename Char_>
		struct ToNodeData<NodeType::TakeAnchor, Char_> : MetaFn<BasicTakeAnchorData<Char_>> {};
		template<typename Char_>
		struct ToNodeData<NodeType::GetAnchor, Char_> : MetaFn<BasicGetAnchorData<Char_>> {};
	}
	
	template<NodeType Type, typename Char_>
	using ToNodeData = typename detail::ToNodeData<Type, Char_>::type;
}
