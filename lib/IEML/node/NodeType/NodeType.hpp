#pragma once

#include <string>
#include "../../usings/usings.hpp"

namespace ieml {
	/// @brief  Enum, storing the type of node
	enum class NodeType {
		Null = 0,
		Raw,
		String,
		List,
		Map,
		Tag,
		File,
		TakeAnchor,
		GetAnchor
	};
	
	/// @brief Creates a string from a node type.
	///
	/// @param NodeType Node type.
	///
	/// @return The node type as a string.
	String get_string_from_node_type(NodeType node_type);
	
	/// @brief Creates a index from a node type.
	///
	/// @param NodeType Node type.
	///
	/// @return The index.
	constexpr Size get_index_from_node_type(NodeType node_type) {
		return static_cast<Size>(node_type);
	}
	
	/// @brief Creates a node type from a index.
	///
	/// @param index Index.
	///
	/// @return The node type.
	constexpr NodeType get_node_type_from_index(Size index) {
		if(index < 9)
			return static_cast<NodeType>(index);
		return NodeType::Null;
	}
}
