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
	String getStringFromNodeType(NodeType nodeType);
	
	/// @brief Creates a index from a node type.
	///
	/// @param NodeType Node type.
	///
	/// @return The index.
	constexpr Size getIndexFromNodeType(NodeType nodeType) {
		return static_cast<Size>(nodeType);
	}
	
	/// @brief Creates a node type from a index.
	///
	/// @param index Index.
	///
	/// @return The node type.
	constexpr NodeType getNodeTypeFromIndex(Size index) {
		if(index < 9)
			return static_cast<NodeType>(index);
		return NodeType::Null;
	}
}
