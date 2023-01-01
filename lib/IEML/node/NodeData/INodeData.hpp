#pragma once
#include "../NodeType/NodeType.hpp"
#include <string>

namespace ieml {
	using llint = long long;
	
	class Node;
	
	/// @brief  Interface for node data
	class INodeData {
	public:
		/// @brief Gets the node type.
		///
		/// @return Returns the node type.
		virtual NodeType getNodeType() = 0;
		
		/// @brief Asks if a node is a scalar.
		///
		/// @return Value if a node is a scalar.
		virtual bool isScalar();
		
		/// @brief Asks if a node has a tag.
		///
		/// @return Value if a node has a tag.
		virtual bool isWithTag();
		
		/// @brief Gets the tag.
		///
		/// @return A tag or throws an exception NotRequestedTypeException.
		virtual std::string getTag();
		
		/// @brief Asks if a node has a tag.
		///
		/// @return Value if a node has a tag.
		virtual bool isFile();
		
		/// @brief Gets the tag.
		///
		/// @return A tag or throws an exception NotRequestedTypeException.
		virtual std::string getFilePath();
		
		/// @brief Gets the string value.
		///
		/// @return A string value or throws an exception NotRequestedTypeException.
		virtual std::string getString();
		
		/// @brief Gets a node from the list by index.
		///
		/// @param index Index of the requested node.
		///
		/// @return A node or throws an exception NotRequestedTypeException.
		virtual Node &at(std::size_t index);
		
		/// @brief Gets a node from the map by key.
		///
		/// @param key Key of the requested node.
		///
		/// @return A node or throws an exception NotRequestedTypeException.
		virtual Node &at(std::string key);
		
		virtual ~INodeData() = default;
	};
}
