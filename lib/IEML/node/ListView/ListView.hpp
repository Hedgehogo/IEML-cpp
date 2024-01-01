#pragma once

namespace ieml {
	template<typename Char_>
	class BasicNode;
	
	template<typename Char_>
	class BasicListView {
	public:
		BasicListView(BasicListData<Char_> const& list, Mark mark);
		
		/// @brief Gets the list size.
		///
		/// @return A list size.
		Size get_size() const;
		
		/// @brief Gets the node list.
		///
		/// @return A node list.
		BasicListData<Char_> const& get_list() const;
		
		/// @brief Gets a node from the list by index.
		///
		/// @param index Index of the requested node.
		///
		/// @return A node.
		Result<BasicNode<Char_> const&, ListException> at(Size index) const;
		
		/// @brief Gets a node from the list by index.
		///
		/// @param index Index of the requested node.
		///
		/// @return A node.
		Result<BasicNode<Char_> const&, ListException> operator[](Size index) const;
	
	private:
		BasicListData<Char_> const& list_;
		Mark mark_;
	};
	
	using ListView = BasicListView<Char>;
}
