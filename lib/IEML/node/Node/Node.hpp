#pragma once

#include <memory>
#include "../../anchor/AnchorKeeper/AnchorKeeper.hpp"
#include "../Mark/Mark.hpp"
#include "../ListView/ListView.hpp"
#include "../MapView/MapView.hpp"
#include "decode/decode.hpp"

namespace ieml {
	template<typename Char_>
	class BasicNode {
	public:
		BasicNode(BasicNodeData<Char_> data, Mark mark = {0, 0});
		
		template<typename T>
		BasicNode(T data, Mark mark = {0, 0});
		
		/// @brief Gets the node defined.
		///
		/// @param Node Node to check.
		///
		/// @return The node defined.
		static bool is_defined(BasicNode const& node);
		
		/// @brief Gets the node defined.
		///
		/// @return The node defined.
		bool is_defined() const;
		
		/// @brief Gets the node mark.
		///
		/// @return The node mark.
		Mark get_mark() const;
		
		/// @brief Gets the node type.
		///
		/// @return The node type.
		NodeType get_type() const;
		
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
		bool is_null() const;
		
		/// @brief Asks if the node is raw.
		///
		/// @return Value whether a node is raw.
		bool is_raw() const;
		
		/// @brief Asks if the node is scalar.
		///
		/// @return Value whether a node is scalar.
		bool is_string() const;
		
		/// @brief Asks if the node is list.
		///
		/// @return Value whether a node is list.
		bool is_list() const;
		
		/// @brief Asks if the node is map.
		///
		/// @return Value whether a node is map.
		bool is_map() const;
		
		/// @brief Asks if a node has a tag.
		///
		/// @return Value if a node has a tag.
		bool is_with_tag() const;
		
		/// @brief Asks if a node has a file path.
		///
		/// @return Value if a node has a file path.
		bool is_file() const;
		
		/// @brief Asks if the node is take anchor.
		///
		/// @return Value whether a node is take anchor.
		bool is_take_anchor() const;
		
		/// @brief Asks if the node is get anchor.
		///
		/// @return Value whether a node is get anchor.
		bool is_get_anchor() const;
		
		/// @brief Recursively gets a child node, excluding Tag, File, take Anchor and get Anchor.
		///
		/// @return A node.
		template<NodeType... Types>
		BasicNode<Char_>& get_clear();
		
		template<NodeType... Types>
		BasicNode<Char_> const& get_clear() const;
		
		/// @brief Recursively gets a child node, excluding Types.
		///
		/// @return A node.
		BasicNode<Char_>& get_clear();
		
		BasicNode<Char_> const& get_clear() const;
		
		/// @brief Gets a child node if the node type is Type, otherwise the current node.
		///
		/// @return A node.
		template<NodeType... Types>
		BasicNode<Char_>& get_clear_data();
		
		template<NodeType... Types>
		BasicNode<Char_> const& get_clear_data() const;
		
		/// @brief Gets the node under the tag if the node type is with the tag, otherwise the current node.
		///
		/// @return A node.
		BasicNode<Char_>& get_clear_tag();
		
		BasicNode<Char_> const& get_clear_tag() const;
		
		/// @brief Gets the node contained in the file, if the node type is a file, otherwise the current node.
		///
		/// @return A node.
		BasicNode<Char_>& get_clear_file();
		
		BasicNode<Char_> const& get_clear_file() const;
		
		/// @brief Gets the node contained in the anchor if the node type is take anchor, otherwise the current node
		///
		/// @return A node.
		BasicNode<Char_>& get_clear_take_anchor();
		
		BasicNode<Char_> const& get_clear_take_anchor() const;
		
		/// @brief Gets the node contained in the anchor if the node type is get anchor, otherwise the current node
		///
		/// @return A node.
		BasicNode<Char_>& get_clear_get_anchor();
		
		BasicNode<Char_> const& get_clear_get_anchor() const;
		
		/// @brief Gets the node contained in the anchor if the node type is anchor, otherwise the current node
		///
		/// @return A node.
		BasicNode<Char_>& get_clear_anchor();
		
		BasicNode<Char_> const& get_clear_anchor() const;
		
		/// @brief Gets the tag.
		///
		/// @return A tag.
		Option<BasicTag<Char_>&> get_tag();
		
		Option<BasicTag<Char_> const&> get_tag() const;
		
		/// @brief Gets the file path.
		///
		/// @return A file path.
		Option<FilePath const&> get_file_path() const;
		
		/// @brief Gets the file anchor keeper.
		///
		/// @return A anchor keeper.
		Option<BasicAnchorKeeper<Char_> const&> get_file_anchor_keeper() const;
		
		/// @brief Gets the take anchor name.
		///
		/// @return A take anchor name.
		Option<BasicString<Char_> const&> get_take_anchor_name() const;
		
		/// @brief Gets the get anchor name.
		///
		/// @return A get anchor name.
		Option<BasicString<Char_> const&> get_get_anchor_name() const;
		
		/// @brief Gets the anchor name.
		///
		/// @return A anchor name.
		Option<BasicString<Char_> const&> get_anchor_name() const;
		
		/// @brief Gets the list size.
		///
		/// @return A size or NodeAnotherTypeException.
		TypeResult<Size> get_list_size() const;
		
		/// @brief Gets the map size.
		///
		/// @return A size or NodeAnotherTypeException.
		TypeResult<Size> get_map_size() const;
		
		/// @brief Gets the size.
		///
		/// @return A size or NodeAnotherTypeException.
		TypeResult<Size> get_size() const;
		
		/// @brief Gets the raw data.
		///
		/// @return A raw data or NodeAnotherTypeException.
		TypeResult<BasicRawData<Char_>&> get_raw();
		
		TypeResult<BasicRawData<Char_> const&> get_raw() const;
		
		/// @brief Gets the string.
		///
		/// @return A string or NodeAnotherTypeException.
		TypeResult<BasicStringData<Char_>&> get_string();
		
		TypeResult<BasicStringData<Char_> const&> get_string() const;
		
		/// @brief Gets the node list.
		///
		/// @return A node list or NodeAnotherTypeException.
		TypeResult<BasicListData<Char_> const&> get_list() const;
		
		/// @brief Gets the node map.
		///
		/// @return A node map or NodeAnotherTypeException.
		TypeResult<BasicMapData<Char_> const&> get_map() const;
		
		/// @brief Gets the node list view.
		///
		/// @return A node list view or NodeAnotherTypeException.
		TypeResult<BasicListView<Char_> > get_list_view() const;
		
		/// @brief Gets the node map view.
		///
		/// @return A node map view or NodeAnotherTypeException.
		TypeResult<BasicMapView<Char_> > get_map_view() const;
		
		/// @brief Gets a node from the list by index.
		///
		/// @param index Index of the requested node.
		///
		/// @return A node or NodeAnotherTypeException.
		ListResult<BasicNode<Char_>&> at(Size index);
		
		ListResult<BasicNode<Char_> const&> at(Size index) const;
		
		/// @brief Gets a node from the list by index.
		///
		/// @param index Index of the requested node.
		///
		/// @return A node or undefined node.
		BasicNode<Char_>& at_or(Size index);
		
		BasicNode<Char_> const& at_or(Size index) const;
		
		/// @brief Gets a node from the map by key.
		///
		/// @param key Key of the requested node.
		///
		/// @return A node or NodeAnotherTypeException.
		MapResult<Char_, BasicNode<Char_>&> at(BasicString<Char_> const& key);
		
		MapResult<Char_, BasicNode<Char_> const&> at(BasicString<Char_> const& key) const;
		
		/// @brief Gets a node from the map by key.
		///
		/// @param key Key of the requested node.
		///
		/// @return A node or undefined node.
		BasicNode<Char_>& at_or(BasicString<Char_> const& key);
		
		BasicNode<Char_> const& at_or(BasicString<Char_> const& key) const;
		
		/// @brief Gets the T value.
		///
		/// @tparam T Value type.
		///
		/// @return A T value or FailedDecodeDataException.
		template<typename T>
		DecodeResult<T> as() const;
		
		/// @brief Gets a node in the passed path or an error at any step.
		///
		/// @param args Path steps, can be: strings for map keys (including literals), numbers for indexes, ieml::clear to call get_clear().
		///
		/// @return A node or NodeAnotherTypeException.
		template<typename... Steps>
		GetResult<Char_, BasicNode<Char_>&> get(Steps&&... steps);
		
		template<typename... Steps>
		GetResult<Char_, BasicNode<Char_> const&> get(Steps&&... steps) const;
		
		/// @brief Gets the T value converted from a node in the passed path or an error at any step or during conversion.
		///
		/// @param args Path steps, can be: strings for map keys (including literals), numbers for indexes, ieml::clear to call get_clear().
		///
		/// @tparam T Value type.
		///
		/// @return A T value or NodeAnotherTypeException or FailedDecodeDataException.
		template<typename T, typename... Steps>
		GetAsResult<Char_, T> get_as(Steps&&... steps) const;
		
		/// @brief Gets the node defined.
		///
		/// @return The node defined.
		explicit operator bool() const;
		
		/// @brief Gets a node from the list by index.
		///
		/// @param index Index of the requested node.
		///
		/// @return A node or NodeAnotherTypeException.
		ListResult<BasicNode<Char_>&> operator[](Size index);
		
		ListResult<BasicNode<Char_> const&> operator[](Size index) const;
		
		/// @brief Gets a node from the map by key.
		///
		/// @param key Key of the requested node.
		///
		/// @return A node or NodeAnotherTypeException.
		MapResult<Char_, BasicNode<Char_>&> operator[](BasicString<Char_> const& key);
		
		MapResult<Char_, BasicNode<Char_> const&> operator[](BasicString<Char_> const& key) const;
		
		/// Does not take marks into account in comparisons
		bool operator==(BasicNode<Char_> const& other) const;
		
		bool operator!=(BasicNode<Char_> const& other) const;
		
		template<typename OtherChar_, typename T>
		friend
		struct detail::DecodeImpl;
		
		template<typename D, typename T>
		friend
		struct GetFromStep;
	
	private:
		template<NodeType Type>
		NodeAnotherTypeException make_type_error() const;
		
		template<NodeType Type>
		TypeResult<ToNodeData<Type, Char_>&> get_typed_data_or_error();
		
		template<NodeType Type>
		TypeResult<ToNodeData<Type, Char_> const&> get_typed_data_or_error() const;
		
		template<NodeType Type>
		Option<ToNodeData<Type, Char_>&> get_typed_data();
		
		template<NodeType Type>
		Option<ToNodeData<Type, Char_> const&> get_typed_data() const;
		
		static BasicNode<Char_> undefined;
		
		BasicNodeData<Char_> data_;
		Mark mark_;
	};
	
	using Node = BasicNode<Char>;
}

#include "../../anchor/AnchorKeeper/AnchorKeeper.inl"
#include "../NodeData/NodeData.inl"
#include "../ListView/ListView.inl"
#include "../MapView/MapView.inl"
#include "decode/decode.inl"
#include "Node.inl"
