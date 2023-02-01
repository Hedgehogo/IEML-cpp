#pragma once
#include <string>

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
	std::string getNodeTypeString(NodeType nodeType);
	
	/// @brief Creates a index from a node type.
	///
	/// @param NodeType Node type.
	///
	/// @return The index.
	constexpr std::size_t getNodeTypeIndex(NodeType nodeType) {
		return static_cast<std::size_t>(nodeType);
	}
	
	/// @brief Creates a node type from a index.
	///
	/// @param std::size_t index.
	///
	/// @return The node type.
	constexpr NodeType getNodeTypeFromIndex(std::size_t index) {
		return static_cast<NodeType>(index);
	}
}
