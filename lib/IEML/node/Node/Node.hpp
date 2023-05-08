#pragma once

#include <memory>
#include "../../anchor/AnchorKeeper/AnchorKeeper.hpp"
#include "../Mark/Mark.hpp"
#include "../exception/NodeAnotherTypeException.hpp"
#include "exception/FailedConvertDataException.hpp"
#include "decode/decode.hpp"

namespace ieml {
	template<typename Char_>
	class BasicNode {
	public:
		template<typename T>
		using TypeResult = Result<T, NodeAnotherTypeException>;
		
		template<typename T>
		using ConvertResult = Result<T, FailedConvertDataException>;
		
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
		
		/// @brief Asks if a node has a file path.
		///
		/// @return Value if a node has a file path.
		bool isFile() const;
		
		/// @brief Asks if the node is take anchor.
		///
		/// @return Value whether a node is take anchor.
		bool isTakeAnchor() const;
		
		/// @brief Asks if the node is get anchor.
		///
		/// @return Value whether a node is get anchor.
		bool isGetAnchor() const;
		
		/// @brief Recursively gets a child node, excluding Tag, File, take Anchor and get Anchor.
		///
		/// @return A node.
		template<NodeType... Types>
		BasicNode<Char_>& getClear();
		template<NodeType... Types>
		const BasicNode<Char_>& getClear() const;
		
		/// @brief Recursively gets a child node, excluding Types.
		///
		/// @return A node.
		BasicNode<Char_>& getClear();
		const BasicNode<Char_>& getClear() const;
		
		/// @brief Gets a child node if the node type is Type, otherwise the current node.
		///
		/// @return A node.
		template<NodeType... Types>
		BasicNode<Char_>& getClearData();
		template<NodeType... Types>
		const BasicNode<Char_>& getClearData() const;
		
		/// @brief Gets the node under the tag if the node type is with the tag, otherwise the current node.
		///
		/// @return A node.
		BasicNode<Char_>& getClearTag();
		const BasicNode<Char_>& getClearTag() const;
		
		/// @brief Gets the node contained in the file, if the node type is a file, otherwise the current node.
		///
		/// @return A node.
		BasicNode<Char_>& getClearFile();
		const BasicNode<Char_>& getClearFile() const;
		
		/// @brief Gets the node contained in the anchor if the node type is take anchor, otherwise the current node
		///
		/// @return A node.
		BasicNode<Char_>& getClearTakeAnchor();
		const BasicNode<Char_>& getClearTakeAnchor() const;
		
		/// @brief Gets the node contained in the anchor if the node type is get anchor, otherwise the current node
		///
		/// @return A node.
		BasicNode<Char_>& getClearGetAnchor();
		const BasicNode<Char_>& getClearGetAnchor() const;
		
		/// @brief Gets the node contained in the anchor if the node type is anchor, otherwise the current node
		///
		/// @return A node.
		BasicNode<Char_>& getClearAnchor();
		const BasicNode<Char_>& getClearAnchor() const;
		
		/// @brief Gets the tag.
		///
		/// @return A tag.
		Option<BasicTag<Char_>> getTag() const;
		
		/// @brief Gets the file path.
		///
		/// @return A file path.
		Option<FilePath> getFilePath() const;
		
		/// @brief Gets the take anchor name.
		///
		/// @return A take anchor name.
		Option<BasicString<Char_>> getTakeAnchorName() const;
		
		/// @brief Gets the get anchor name.
		///
		/// @return A get anchor name.
		Option<BasicString<Char_>> getGetAnchorName() const;
		
		/// @brief Gets the anchor name.
		///
		/// @return A anchor name.
		Option<BasicString<Char_>> getAnchorName() const;
		
		/// @brief Gets the list size.
		///
		/// @return A size or throws an exception NodeAnotherTypeException.
		TypeResult<Size> getListSize() const;
		
		/// @brief Gets the map size.
		///
		/// @return A size or throws an exception NodeAnotherTypeException.
		TypeResult<Size> getMapSize() const;
		
		/// @brief Gets the size.
		///
		/// @return A size or throws an exception NodeAnotherTypeException.
		TypeResult<Size> getSize() const;
		
		/// @brief Gets the node list.
		///
		/// @return A node list or throws an exception NodeAnotherTypeException.
		TypeResult<const BasicListData<Char_>&> getList() const;
		
		/// @brief Gets the node map.
		///
		/// @return A node map or throws an exception NodeAnotherTypeException.
		TypeResult<const BasicMapData<Char_>&> getMap() const;
		
		/// @brief Gets the T value.
		///
		/// @tparam T Value type.
		///
		/// @return A T value or throws an exception FailedConvertDataException.
		template<typename T>
		ConvertResult<T> as() const;
		
		/// @brief Gets a node from the list by index.
		///
		/// @param index Index of the requested node.
		///
		/// @return A node or throws an exception NodeAnotherTypeException.
		Option<BasicNode<Char_>&> at(Size index);
		
		Option<const BasicNode<Char_>&> at(Size index) const;
		
		/// @brief Gets a node from the map by key.
		///
		/// @param key Key of the requested node.
		///
		/// @return A node or throws an exception NodeAnotherTypeException.
		Option<BasicNode<Char_>&> at(const BasicString<Char_>& key);
		
		Option<const BasicNode<Char_>&> at(const BasicString<Char_>& key) const;
		
		/// @brief Gets the node defined.
		///
		/// @return The node defined.
		explicit operator bool() const;
		
		/// @brief Gets a node from the list by index.
		///
		/// @param index Index of the requested node.
		///
		/// @return A node or throws an exception NodeAnotherTypeException.
		Option<BasicNode<Char_>&> operator[](Size index);
		
		Option<const BasicNode<Char_>&> operator[](Size index) const;
		
		/// @brief Gets a node from the map by key.
		///
		/// @param key Key of the requested node.
		///
		/// @return A node or throws an exception NodeAnotherTypeException.
		Option<BasicNode<Char_>&> operator[](const BasicString<Char_>& key);
		
		Option<const BasicNode<Char_>&> operator[](const BasicString<Char_>& key) const;
		
		template<typename OtherChar_, typename T>
		friend
		struct detail::DecodeImpl;
		
		template<typename D, typename T>
		friend
		struct GetFromStep;
	
	private:
		template<typename T, typename E>
		Result<const T&, E> getType(E e) const;
		
		template<typename T, typename E>
		Result<T&, E> getType(E e);
		
		template<typename T>
		Option<const T&> getType() const;
		
		template<typename T>
		Option<T&> getType();
		
		static BasicNode<Char_> undefined;
		
		BasicNodeData<Char_> data_;
		Mark mark_;
	};
	
	using Node = BasicNode<Char>;
	
	template<typename Char_ = Char>
	BasicNode<Char_> fromFile(FilePath&& filePath, RcPtr<BasicAnchorKeeper<Char_>> anchorKeeper = makeRcPtr<BasicAnchorKeeper<Char_>>());
	
	template<typename Char_ = Char>
	BasicNode<Char_> from(const BasicString<Char_>& inputStr, RcPtr<BasicAnchorKeeper<Char_>> anchorKeeper = makeRcPtr<BasicAnchorKeeper<Char_>>());
}

#include "../../anchor/AnchorKeeper/AnchorKeeper.inl"
#include "../NodeData/NodeData.inl"
#include "decode/decode.inl"
#include "Node.inl"
