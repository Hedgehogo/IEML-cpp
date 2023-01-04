#pragma once
#include "../NodeData/INodeData.hpp"
#include "../Mark/Mark.hpp"
#include "as/as.hpp"
#include <memory>

namespace ieml {
	class Node {
	public:
		template <typename T>
		friend struct AsIf;
		
		using PData = std::unique_ptr<INodeData>;
		
	private:
		PData data;
		Mark mark;
		
	public:
		Node(const std::string &config);
		
		Node(PData data, Mark mark = {0, 0});
		
		/// @brief Gets the node mark.
		///
		/// @return The node mark.
		Mark getMark();
		
		/// @brief Gets the node type.
		///
		/// @return The node type.
		NodeType getType();
		
		/// @brief Asks if a node has a tag.
		///
		/// @return Value if a node has a tag.
		bool isWithTag();
		
		/// @brief Gets the tag.
		///
		/// @return A tag or throws an exception NotRequestedTypeException.
		std::string getTag();
		
		/// @brief Asks if a node has a tag.
		///
		/// @return Value if a node has a tag.
		bool isFile();
		
		/// @brief Gets the tag.
		///
		/// @return A tag or throws an exception NotRequestedTypeException.
		std::string getFilePath();
		
		/// @brief Gets the size.
		///
		/// @return A size or throws an exception NotRequestedTypeException.
		std::size_t getSize();
		
		/// @brief Gets the node map.
		///
		/// @return A node map or throws an exception NotRequestedTypeException.
		std::map<std::string, Node> &getMap();
		
		/// @brief Gets the T value.
		///
		/// @tparam T Value type.
		///
		/// @return A T value or throws an exception NotRequestedTypeException.
		template<typename T> T as();
		
		/// @brief Gets a node from the list by index.
		///
		/// @param index Index of the requested node.
		///
		/// @return A node or throws an exception NotRequestedTypeException.
		Node &at(std::size_t index);
		
		/// @brief Gets a node from the map by key.
		///
		/// @param key Key of the requested node.
		///
		/// @return A node or throws an exception NotRequestedTypeException.
		Node &at(std::string key);
	};
	
	Node file(const std::string& filePath);
}

#include "Node.inl"
