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
	};
	
	/// @brief Creates a string from a node type.
	///
	/// @param NodeType Node type.
	///
	/// @return The node type as a string.
	String getNodeTypeString(NodeType nodeType);
	
	/// @brief Creates a index from a node type.
	///
	/// @param NodeType Node type.
	///
	/// @return The index.
	constexpr Size getNodeTypeIndex(NodeType nodeType) {
		return static_cast<Size>(nodeType);
	}
	
	/// @brief Creates a node type from a index.
	///
	/// @param index Index.
	///
	/// @return The node type.
	constexpr NodeType getNodeTypeFromIndex(Size index) {
		if(index < 5)
			return static_cast<NodeType>(index);
		return NodeType::Null;
	}
}
