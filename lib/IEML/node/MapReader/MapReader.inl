//included into ../Node/Node.hpp

namespace ieml {
	template<typename Char_>
	MapReader<Char_>::MapReader(BasicMapData<Char_> const& map, Mark mark) : map_(map), mark_(mark) {
	}
	
	template<typename Char_>
	auto MapReader<Char_>::extra_keys() -> Option<KeyContainer> {
		if(requested_.size() != map_.size()) {
			KeyContainer extra_keys{};
			extra_keys.reserve(map_.size() - requested_.size());
			for(auto& item: map_) {
				if(!requested_.contains(&item.first)) {
					extra_keys.emplace(item.first);
				}
			}
			return {std::move(extra_keys)};
		}
		return {};
	}
	
	template<typename Char_>
	Result<BasicNode<Char_> const&, MapException<Char_> > MapReader<Char_>::at(BasicString<Char_> const& key) {
		return operator[](key);
	}
	
	template<typename Char_>
	template<typename... Steps>
	GetResult<Char_, const ieml::BasicNode<Char_>&> MapReader<Char_>::get(BasicString<Char_> const& key, Steps&& ... steps) {
		auto item{at(key)};
		if(item) {
			return item.ok().get(std::forward<Steps>(steps)...);
		}
		return GetResult<Char_, BasicNode<Char_> const&>::Error({std::move(item.error())});
	}
	
	template<typename Char_>
	template<typename T, typename... Steps>
	GetAsResult<Char_, T> MapReader<Char_>::get_as(BasicString<Char_> const& key, Steps&& ... steps) {
		auto item_result{at(key)};
		for(auto& item: item_result.ok_or_none()) {
			return item.template get_as<T>(std::forward<Steps>(steps)...);
		}
		return GetAsResult<Char_, T>::Ok(GetResult<Char_, T>::Error(std::move(item_result.error())));
	}
	
	template<typename Char_>
	Result<BasicNode<Char_> const&, MapException<Char_> > MapReader<Char_>::operator[](BasicString<Char_> const& key) {
		if(auto find{map_.find(key)}; find != map_.end()) {
			requested_.emplace(&find->first);
			return Result<BasicNode<Char_> const&, MapException<Char_> >::Ok(find->second);
		}
		return Result<BasicNode<Char_> const&, MapException<Char_> >::Error({MapException{mark_, key}});
	}
}
