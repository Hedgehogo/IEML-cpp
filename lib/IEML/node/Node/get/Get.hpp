#pragma once

#include <option_result/Error.hpp>
#include <option_result.hpp>
#include "../../../usings/usings.hpp"
#include "../../../helpers/MetaFn/MetaFn.hpp"
#include "../../exception/NodeAnotherTypeException.hpp"

namespace ieml::detail {
	struct Clear {};
}

namespace ieml {
	template<typename Char_>
	class BasicNode;
	
	constexpr auto clear = detail::Clear{};
}

namespace ieml::detail {
	
	template<typename T_>
	using GetResult = Result<T_, NodeAnotherTypeException>;
	
	template<typename Char_, typename T_>
	class GetStep;
	
	template<typename Char_>
	class GetStep<Char_, Size> {
	private:
		Size data_;
	
	public:
		GetStep(Size data) : data_(data) {}
		
		GetResult<BasicNode<Char_>&> get(BasicNode<Char_>& node) const;
		
		GetResult<BasicNode<Char_> const&> get(BasicNode<Char_> const& node) const;
	};
	
	template<typename Char_>
	class GetStep<Char_, BasicString<Char_>> {
	private:
		BasicString<Char_> data_;
	
	public:
		GetStep(const BasicString<Char_>& data) : data_(data) {}
		
		GetResult<BasicNode<Char_>&> get(BasicNode<Char_>& node) const;
		
		GetResult<BasicNode<Char_> const&> get(BasicNode<Char_> const& node) const;
	};
	
	template<typename Char_>
	class GetStep<Char_, detail::Clear> {
	public:
		GetStep(Clear data) {}
		
		GetResult<BasicNode<Char_>&> get(BasicNode<Char_>& node) const;
		
		GetResult<BasicNode<Char_> const&> get(BasicNode<Char_> const& node) const;
	};
	
	template<typename Char_>
	GetResult<BasicNode<Char_>&> get(BasicNode<Char_>& node);
	
	template<typename Char_, typename T, typename... Ts>
	GetResult<BasicNode<Char_>&> get(BasicNode<Char_>& node, GetStep<Char_, T>&& step, GetStep<Char_, Ts>&&... steps);
	
	template<typename Char_>
	GetResult<BasicNode<Char_> const&> get(BasicNode<Char_> const& node);
	
	template<typename Char_, typename T, typename... Ts>
	GetResult<BasicNode<Char_> const&> get(BasicNode<Char_> const& node, GetStep<Char_, T>&& step, GetStep<Char_, Ts>&&... steps);
	
	template<typename Char_, typename T_>
	struct GetStepType;
	template<typename Char_>
	struct GetStepType<Char_, unsigned> : public MetaFn<Size> {};
	template<typename Char_>
	struct GetStepType<Char_, Size> : public MetaFn<Size> {};
	template<typename Char_>
	struct GetStepType<Char_, char const*> : public MetaFn<BasicString<Char_>> {};
	template<typename Char_, Size N>
	struct GetStepType<Char_, char const[N]> : public MetaFn<BasicString<Char_>> {};
	template<typename Char_, Size N>
	struct GetStepType<Char_, char const(&)[N]> : public MetaFn<BasicString<Char_>> {};
	template<typename Char_>
	struct GetStepType<Char_, const BasicString<Char_>&> : public MetaFn<BasicString<Char_>> {};
	template<typename Char_>
	struct GetStepType<Char_, const Clear&> : public MetaFn<Clear> {};
}

namespace ieml {
	template<typename Char_, typename T_>
	using GetStep = detail::GetStep<Char_, typename detail::GetStepType<Char_, T_>::type>;
}

#include "get.inl"
