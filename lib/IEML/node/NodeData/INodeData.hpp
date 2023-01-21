#pragma once
#include <string>
#include <map>
#include "../../fileSystem/fileSystem.hpp"
#include "../NodeType/NodeType.hpp"

namespace ieml {
	using llint = long long;
	
	class Node;
	
	/// @brief  Interface for node data
	class INodeData {
	public:
		/// @brief Gets the node type.
		///
		/// @return Returns the node type.
		virtual NodeType getNodeType() const = 0;
		
		/// @brief Asks if a node has a tag.
		///
		/// @return Value if a node has a tag.
		virtual bool isWithTag() const;
		
		/// @brief Gets the tag.
		///
		/// @return A tag or throws an exception NotRequestedTypeException.
		virtual std::string getTag() const;
		
		/// @brief Asks if a node has a tag.
		///
		/// @return Value if a node has a tag.
		virtual bool isFile() const;
		
		/// @brief Gets the tag.
		///
		/// @return A tag or throws an exception NotRequestedTypeException.
		virtual fs::path getFilePath() const;
		
		/// @brief Gets the size.
		///
		/// @return A size or throws an exception NotRequestedTypeException.
		virtual std::size_t getSize() const;
		
		/// @brief Gets the string value.
		///
		/// @return A string value or throws an exception NotRequestedTypeException.
		virtual std::string getString() const;
		
		/// @brief Gets the node list.
		///
		/// @return A node list or throws an exception NotRequestedTypeException.
		virtual std::vector<Node> getList() const;
		
		/// @brief Gets the node map.
		///
		/// @return A node map or throws an exception NotRequestedTypeException.
		virtual std::map<std::string, Node> getMap() const;
		
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
		
		/// @brief Gets a copy of the node data.
		///
		/// @return A node data.
		virtual INodeData *copy() const = 0;
		
		virtual ~INodeData() = default;
	};
}
