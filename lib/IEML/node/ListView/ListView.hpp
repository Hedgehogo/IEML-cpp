#pragma once

#include "../Mark/Mark.hpp"
#include "../NodeData/NodeData.hpp"
#include "../exception/results.hpp"

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
		
		/// @brief Gets a node in the passed path or an error at any step.
		///
		/// @param args Path steps, can be: strings for map keys (including literals), numbers for indexes, ieml::clear to call get_clear().
		///
		/// @return A node or NodeAnotherTypeException.
		template<typename... Steps>
		GetResult<Char_, BasicNode<Char_> const&> get(size_t index, Steps&&... steps) const;
		
		/// @brief Gets the T value converted from a node in the passed path or an error at any step or during conversion.
		///
		/// @param args Path steps, can be: strings for map keys (including literals), numbers for indexes, ieml::clear to call get_clear().
		///
		/// @tparam T Value type.
		///
		/// @return A T value or NodeAnotherTypeException or FailedDecodeDataException.
		template<typename T, typename... Steps>
		GetAsResult<Char_, T> get_as(size_t index, Steps&&... steps) const;
		
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
