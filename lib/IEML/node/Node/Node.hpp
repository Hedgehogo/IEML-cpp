#pragma once

#include <memory>
#include "../Mark/Mark.hpp"
#include "../../anchor/AnchorKeeper/AnchorKeeper.hpp"
#include "decode/decode.hpp"

namespace ieml {
	template<typename Char_>
	class BasicNode {
	public:
		template<typename OtherChar_, typename T>
		friend struct detail::DecodeImpl;
		
		friend class BasicAnchorKeeper<Char_>;
	
	private:
		static BasicNode<Char_> undefined;
		
		BasicNodeData<Char_> data;
		Mark mark;
		
		static const BasicNodeData<Char_>& getDataFrom(const BasicNodeData<Char_>& data);
		
		static BasicNodeData<Char_>& getDataFrom(BasicNodeData<Char_>& data);
		
		static const BasicFileData<Char_>* getFileFrom(const BasicNodeData<Char_>& data);
		
		static BasicFileData<Char_>* getFileFrom(BasicNodeData<Char_>& data);
		
		static const BasicTagData<Char_>* getTagFrom(const BasicNodeData<Char_>& data);
		
		static BasicTagData<Char_>* getTagFrom(BasicNodeData<Char_>& data);
		
		static const BasicTakeAnchorData<Char_>* getTakeAnchorFrom(const BasicNodeData<Char_>& data);
		
		static BasicTakeAnchorData<Char_>* getTakeAnchorFrom(BasicNodeData<Char_>& data);
		
		static const BasicGetAnchorData<Char_>* getGetAnchorFrom(const BasicNodeData<Char_>& data);
		
		static BasicGetAnchorData<Char_>* getGetAnchorFrom(BasicNodeData<Char_>& data);
		
		template<typename T, typename E>
		const T& getType(E e) const;
		
		template<typename T, typename E>
		T& getType(E e);
	
	public:
		BasicNode(BasicNodeData<Char_> data, Mark mark = {0, 0});
		
		template<typename T>
		BasicNode(T data, Mark mark = {0, 0});
		
		template<typename T>
		BasicNode(T data, FilePath filePath, Mark mark = {0, 0});
		
		/// @brief Gets the node defined.
		///
		/// @param Node Node to check.
		///
		/// @return The node defined.
		static bool isDefined(const BasicNode& node);
		
		/// @brief Gets the node defined.
		///
		/// @return The node defined.
		bool isDefined() const;
		
		/// @brief Gets the node mark.
		///
		/// @return The node mark.
		Mark getMark() const;
		
		/// @brief Gets the node type.
		///
		/// @return The node type.
		NodeType getType() const;
		
		/// @brief Asks if the node is type.
		///
		/// @tparam Type Node type.
		///
		/// @return Value whether a node is type.
		template<NodeType Type>
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
		bool isWithTag() const;
		
		/// @brief Gets the tag.
		///
		/// @return A tag.
		Option<BasicTag<Char_>> getTag() const;
		
		/// @brief Asks if a node has a file path.
		///
		/// @return Value if a node has a file path.
		bool isFile() const;
		
		/// @brief Gets the file path.
		///
		/// @return A file path.
		Option<FilePath> getFilePath() const;
		
		/// @brief Asks if the node is take anchor.
		///
		/// @return Value whether a node is take anchor.
		bool isTakeAnchor() const;
		
		/// @brief Gets the take anchor name.
		///
		/// @return A take anchor name.
		Option<BasicString<Char_>> getTakeAnchorName() const;
		
		/// @brief Asks if the node is get anchor.
		///
		/// @return Value whether a node is get anchor.
		bool isGetAnchor() const;
		
		/// @brief Gets the get anchor name.
		///
		/// @return A get anchor name.
		Option<BasicString<Char_>> getGetAnchorName() const;
		
		/// @brief Gets the anchor name.
		///
		/// @return A anchor name.
		Option<BasicString<Char_>> getAnchorName() const;
		
		/// @brief Gets the size.
		///
		/// @return A size or throws an exception NodeAnotherTypeException.
		Size getSize() const;
		
		/// @brief Gets the node list.
		///
		/// @return A node list or throws an exception NodeAnotherTypeException.
		const BasicListData<Char_>& getList() const;
		
		/// @brief Gets the node map.
		///
		/// @return A node map or throws an exception NodeAnotherTypeException.
		const BasicMapData<Char_>& getMap() const;
		
		/// @brief Gets the T value.
		///
		/// @tparam T Value type.
		///
		/// @return A T value or throws an exception FailedConvertDataException.
		template<typename T>
		T as() const;
		
		/// @brief Gets the T value.
		///
		/// @tparam T Value type.
		///
		/// @param defaultValue Default value.
		///
		/// @return A T value or default T value.
		template<typename T>
		T asOr(T&& defaultValue) const;
		
		/// @brief Gets the T pointer value.
		///
		/// @tparam Type Value pointer type.
		/// @tparam ArgsTypes Types of arguments for constructor call.
		///
		/// @param args Arguments to call the constructor.
		///
		/// @return Pointer to an object or to an object created using the default constructors.
		template<typename Type, typename... ArgsTypes>
		Type* asPtrOr(ArgsTypes... args) const;
		
		/// @brief Gets a node from the list by index.
		///
		/// @param index Index of the requested node.
		///
		/// @return A node or throws an exception NodeAnotherTypeException.
		BasicNode<Char_>& at(Size index);
		
		const BasicNode<Char_>& at(Size index) const;
		
		/// @brief Gets a node from the map by key.
		///
		/// @param key Key of the requested node.
		///
		/// @return A node or throws an exception NodeAnotherTypeException.
		BasicNode<Char_>& at(const BasicString<Char_>& key);
		
		const BasicNode<Char_>& at(const BasicString<Char_>& key) const;
		
		/// @brief Gets the node defined.
		///
		/// @return The node defined.
		explicit operator bool() const;
		
		/// @brief Gets a node from the list by index.
		///
		/// @param index Index of the requested node.
		///
		/// @return A node or throws an exception NodeAnotherTypeException.
		BasicNode<Char_>& operator[](Size index);
		
		const BasicNode<Char_>& operator[](Size index) const;
		
		/// @brief Gets a node from the map by key.
		///
		/// @param key Key of the requested node.
		///
		/// @return A node or throws an exception NodeAnotherTypeException.
		BasicNode<Char_>& operator[](const BasicString<Char_>& key);
		
		const BasicNode<Char_>& operator[](const BasicString<Char_>& key) const;
	};
	
	using Node = BasicNode<Char>;
	
	template<typename Char_ = Char>
	BasicNode<Char_> fromFile(FilePath&& filePath, Rc<BasicAnchorKeeper<Char_>> anchorKeeper = makeRc<BasicAnchorKeeper<Char_>>());
	
	template<typename Char_ = Char>
	BasicNode<Char_> from(const BasicString<Char_>& inputStr, Rc<BasicAnchorKeeper<Char_>> anchorKeeper = makeRc<BasicAnchorKeeper<Char_>>());
}

#include "../../anchor/AnchorKeeper/AnchorKeeper.inl"
#include "../NodeData/NodeData.inl"
#include "decode/decode.inl"
#include "Node.inl"
