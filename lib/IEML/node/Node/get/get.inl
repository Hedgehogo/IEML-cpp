//included into get.hpp

namespace ieml::detail {
	template<typename Char_, typename T>
	GetResult<Char_, T&> get_node(T& node) {
		return GetResult<Char_, T&>::Ok(node);
	}
	
	template<typename Char_, typename T, typename Step, typename... Steps>
	GetResult<Char_, T&> get_node(T& node, Step&& step, Steps&& ... steps) {
		constexpr bool is_correct_type{
			std::is_constructible_v<BasicString<Char_>, Step> ||
			std::is_constructible_v<Size, Step> ||
			std::is_constructible_v<Clear, Step>
		};
		static_assert(is_correct_type, "Invalid type as a Node::get() parameter");
		
		if constexpr(std::is_constructible_v<BasicString<Char_>, Step>) {
			String key{step};
			auto item_result{node.at(key)};
			for(auto& item: item_result.ok_or_none()) {
				return get_node<Char_>(item, std::forward<Steps>(steps)...);
			}
			return GetResult<Char_, T&>::Error(
				item_result.error().template move_cast<NodeAnotherTypeException, ListException, MapException<Char_> >()
			);
		} else if constexpr(std::is_constructible_v<Size, Step>) {
			Size index = step;
			auto item_result{node.at(index)};
			for(auto& item: item_result.ok_or_none()) {
				return get_node<Char_>(item, std::forward<Steps>(steps)...);
			}
			return GetResult<Char_, T&>::Error(item_result.error().template move_upcast<MapException<Char_> >());
		}
		return get_node<Char_>(node.get_clear(), std::forward<Steps>(steps)...);
	}
}