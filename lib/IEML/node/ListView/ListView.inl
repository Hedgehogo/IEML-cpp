//included into ../Node/Node.hpp

namespace ieml {
	template<typename Char_>
	BasicListView<Char_>::BasicListView(const BasicListData<Char_>& list, Mark mark) : list_(list), mark_(mark) {
	}
	
	template<typename Char_>
	Size BasicListView<Char_>::get_size() const {
		return list_.size();
	}
	
	template<typename Char_>
	BasicListData<Char_> const& BasicListView<Char_>::get_list() const {
		return list_;
	}
	
	template<typename Char_>
	Result<BasicNode<Char_> const&, ListException> BasicListView<Char_>::at(Size index) const {
		return operator[](index);
	}
	
	template<typename Char_>
	template<typename... Steps>
	GetResult<Char_, ieml::BasicNode<Char_> const&> BasicListView<Char_>::get(size_t index, Steps&& ... steps) const {
		auto item{at(index)};
		if(item) {
			return item.ok().get(std::forward<Steps>(steps)...);
		}
		return GetResult<Char_, BasicNode<Char_> const&>::Error({std::move(item.error())});
	}
	
	template<typename Char_>
	template<typename T, typename... Steps>
	GetAsResult<Char_, T> BasicListView<Char_>::get_as(size_t index, Steps&& ... steps) const {
		auto item_result{at(index)};
		for(auto& item: item_result.ok_or_none()) {
			return item.template get_as<T>(std::forward<Steps>(steps)...);
		}
		return GetAsResult<Char_, T>::Ok(GetResult<Char_, T>::Error(std::move(item_result.error())));
	}
	
	template<typename Char_>
	Result<BasicNode<Char_> const&, ListException> BasicListView<Char_>::operator[](Size index) const {
		auto size{list_.size()};
		if(size > index) {
			return Result<BasicNode<Char_> const&, ListException>::Ok(list_.at(index));
		}
		return Result<BasicNode<Char_> const&, ListException>::Error(ListException{mark_, index, size});
	}
}
