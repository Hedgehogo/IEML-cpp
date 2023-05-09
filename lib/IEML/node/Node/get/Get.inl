//included into ../Node.hpp

namespace ieml::detail {
	template<typename Char_>
	GetResult<BasicNode<Char_>&> GetStep<Char_, Size>::get(BasicNode<Char_>& node) const {
		return node.at(data_);
	}
	
	template<typename Char_>
	GetResult<const BasicNode<Char_>&> GetStep<Char_, Size>::get(const BasicNode<Char_>& node) const {
		return node.at(data_);
	}
	
	template<typename Char_>
	GetResult<BasicNode<Char_>&> GetStep<Char_, BasicString<Char_>>::get(BasicNode<Char_>& node) const {
		return node.at(data_);
	}
	
	template<typename Char_>
	GetResult<const BasicNode<Char_>&> GetStep<Char_, BasicString<Char_>>::get(const BasicNode<Char_>& node) const {
		return node.at(data_);
	}
	
	template<typename Char_>
	GetResult<BasicNode<Char_>&> GetStep<Char_, Clear>::get(BasicNode<Char_>& node) const {
		return GetResult<BasicNode<Char_>&>::Ok(node.getClear());
	}
	
	template<typename Char_>
	GetResult<const BasicNode<Char_>&> GetStep<Char_, Clear>::get(const BasicNode<Char_>& node) const {
		return GetResult<const BasicNode<Char_>&>::Ok(node.getClear());
	}
	
	template<typename Char_>
	GetResult<BasicNode<Char_>&> get(BasicNode<Char_>& node) {
		return Result<BasicNode<Char_>&, NodeAnotherTypeException>::Ok(node);
	}
	
	template<typename Char_, typename T, typename... Ts>
	GetResult<ieml::BasicNode<Char_>&> get(BasicNode<Char_>& node, GetStep<Char_, T>&& step, GetStep<Char_, Ts>&& ... steps) {
		auto item{step.get(node)};
		if(item.is_ok()) {
			return get(item.ok(), std::forward<GetStep<Char_, Ts> >(steps)...);
		}
		return item;
	}
	
	template<typename Char_>
	GetResult<const BasicNode<Char_>&> get(const BasicNode<Char_>& node) {
		return Result<BasicNode<Char_> const&, NodeAnotherTypeException>::Ok(node);
	}
	
	template<typename Char_, typename T, typename... Ts>
	GetResult<const BasicNode<Char_>&> get(const BasicNode<Char_>& node, GetStep<Char_, T>&& step, GetStep<Char_, Ts>&& ... steps) {
		auto item{step.get(node)};
		if(item.is_ok()) {
			return get(item.ok(), std::forward<Ts>(steps)...);
		}
		return item;
	}
}