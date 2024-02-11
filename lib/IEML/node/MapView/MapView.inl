//included into ../Node/Node.hpp

namespace ieml {
	template<typename Char_>
	BasicMapView<Char_>::BasicMapView(const BasicMapData<Char_>& map, Mark mark) : map_(map), mark_(mark) {
	}
	
	template<typename Char_>
	Size BasicMapView<Char_>::get_size() const {
		return map_.size();
	}
	
	template<typename Char_>
	BasicMapData<Char_> const& BasicMapView<Char_>::get_map() const {
		return map_;
	}
	
	template<typename Char_>
	Result<BasicNode<Char_> const&, MapException<Char_> > BasicMapView<Char_>::at(BasicString<Char_> const& key) const {
		return operator[](key);
	}
	
	template<typename Char_>
	template<typename... Steps>
	GetResult<Char_, const ieml::BasicNode<Char_>&> BasicMapView<Char_>::get(const BasicString<Char_>& key, Steps&& ... steps) const {
		auto item{at(key)};
		if(item) {
			return item.ok().get(std::forward<Steps>(steps)...);
		}
		return GetResult<Char_, BasicNode<Char_> const&>::Error({std::move(item.error())});
	}
	
	template<typename Char_>
	template<typename T, typename... Steps>
	GetAsResult<Char_, T> BasicMapView<Char_>::get_as(const BasicString<Char_>& key, Steps&& ... steps) const {
		auto item_result{at(key)};
		for(auto& item: item_result.ok_or_none()) {
			return item.template get_as<T>(std::forward<Steps>(steps)...);
		}
		return GetAsResult<Char_, T>::Ok(GetResult<Char_, T>::Error(std::move(item_result.error())));
	}
	
	template<typename Char_>
	Result<BasicNode<Char_> const&, MapException<Char_> > BasicMapView<Char_>::operator[](BasicString<Char_> const& key) const {
		auto size{map_.size()};
		if(auto find{map_.find(key)}; find != map_.end()) {
			return Result<BasicNode<Char_> const&, MapException<Char_> >::Ok(find->second);
		}
		return Result<BasicNode<Char_> const&, MapException<Char_> >::Error({MapException{mark_, key}});
	}
}
