#pragma once

#include <option_result/Error.hpp>
#include <option_result/option_result.hpp>
#include "../../../usings/usings.hpp"
#include "../../../helpers/MetaFn/MetaFn.hpp"
#include "../../exception/NodeAnotherType/NodeAnotherTypeException.hpp"

namespace ieml {
	namespace detail {
		struct Clear {};
		
		template<typename Char_, typename T>
		GetResult<Char_, T&> getNode(T& node);
		
		template<typename Char_, typename T, typename Step, typename... Steps>
		GetResult<Char_, T&> getNode(T& node, Step&& step, Steps&&... steps);
	}
	
	constexpr auto clear = detail::Clear{};
}

#include "get.inl"
