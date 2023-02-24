#pragma once

#include <memory>
#include "../NodeData/NodeData.hpp"
#include "../Mark/Mark.hpp"
#include "as/as.hpp"

namespace ieml {
	class Node {
	public:
		template <typename T>
		friend
		struct detail::DecodeImpl;
		
		friend class RefKeeper;
	
	private:
		static Node undefined;
		
		NodeData data;
		Mark mark;
		
		static const NodeData& getDataFrom(const NodeData& data);
		
		static NodeData& getDataFrom(NodeData& data);
		
		static const FileData* getFileFrom(const NodeData& data);
		
		static FileData* getFileFrom(NodeData& data);
		
		static const TagData* getTagFrom(const NodeData& data);
		
		static TagData* getTagFrom(NodeData& data);
		
		template <typename T, typename E>
		const T& getT(E e) const;
		
		template <typename T, typename E>
		T& getT(E e);
	
	public:
		Node(const std::string& config);
		
		Node(NodeData data, Mark mark = {0, 0});
		
		template <typename T>
		Node(T data, Mark mark = {0, 0});
		
		template <typename T>
		Node(T data, FilePath filePath, Mark mark = {0, 0});
		
		/// @brief Gets the node defined.
		///
		/// @param Node Node to check.
		///
		/// @return The node defined.
		static bool isDefined(const Node& node);
		
		/// @brief Gets the node defined.
		///
		/// @return The node defined.
		bool isDefined() const;
		
		/// @brief Gets the node mark.
		///
		/// @return The node mark.
		Mark getMark();
		
		/// @brief Gets the node type.
		///
		/// @return The node type.
		NodeType getType() const;
		
		/// @brief Asks if the node is type.
		///
		/// @tparam Type Node type.
		///
		/// @return Value whether a node is type.
		template <NodeType Type>
		bool is() const;
		
		/// @brief Asks if the node is null.
		///
		/// @return Value whether a node is null.
		bool isNull() const;
		
		/// @brief Asks if the node is raw.
		///
		/// @return Value whether a node is raw.
		bool isRaw() const;
		
		/// @brief Asks if the node is scalar.
		///
		/// @return Value whether a node is scalar.
		bool isString() const;
		
		/// @brief Asks if the node is list.
		///
		/// @return Value whether a node is list.
		bool isList() const;
		
		/// @brief Asks if the node is map.
		///
		/// @return Value whether a node is map.
		bool isMap() const;
		
		/// @brief Asks if a node has a tag.
		///
		/// @return Value if a node has a tag.
		bool isWithTag();
		
		/// @brief Gets the tag.
		///
		/// @return A tag or throws an exception NotRequestedTypeException.
		Tag getTag();
		
		/// @brief Asks if a node has a tag.
		///
		/// @return Value if a node has a tag.
		bool isFile();
		
		/// @brief Gets the tag.
		///
		/// @return A tag or throws an exception NotRequestedTypeException.
		FilePath getFilePath();
		
		/// @brief Gets the size.
		///
		/// @return A size or throws an exception NotRequestedTypeException.
		std::size_t getSize();
		
		/// @brief Gets the node list.
		///
		/// @return A node list or throws an exception NotRequestedTypeException.
		ListData getList() const;
		
		/// @brief Gets the node map.
		///
		/// @return A node map or throws an exception NotRequestedTypeException.
		MapData getMap();
		
		/// @brief Gets the T value.
		///
		/// @tparam T Value type.
		///
		/// @return A T value or throws an exception NotRequestedTypeException.
		template <typename T>
		T as() const;
		
		/// @brief Gets the T value.
		///
		/// @tparam T Value type.
		///
		/// @param defaultValue Default value.
		///
		/// @return A T value or default T value.
		template <typename T>
		T asDefault(T&& defaultValue) const;
		
		/// @brief Gets the T pointer value.
		///
		/// @tparam Type Value pointer type.
		/// @tparam ArgsTypes Types of arguments for constructor call.
		///
		/// @param args Arguments to call the constructor.
		///
		/// @return Pointer to an object or to an object created using the default constructors.
		template <typename Type, typename... ArgsTypes>
		Type* asDefaultPtr(ArgsTypes... args) const;
		
		/// @brief Gets a node from the list by index.
		///
		/// @param index Index of the requested node.
		///
		/// @return A node or throws an exception NotRequestedTypeException.
		Node& at(std::size_t index);
		
		/// @brief Gets a node from the map by key.
		///
		/// @param key Key of the requested node.
		///
		/// @return A node or throws an exception NotRequestedTypeException.
		Node& at(std::string key);
		
		/// @brief Gets the node defined.
		///
		/// @return The node defined.
		explicit operator bool() const;
		
		/// @brief Gets a node from the list by index.
		///
		/// @param index Index of the requested node.
		///
		/// @return A node or throws an exception NotRequestedTypeException.
		Node& operator[](std::size_t index);
		
		/// @brief Gets a node from the map by key.
		///
		/// @param key Key of the requested node.
		///
		/// @return A node or throws an exception NotRequestedTypeException.
		Node& operator[](std::string key);
	};
	
	Node file(const FilePath& filePath);
}

#include "Node.inl"
