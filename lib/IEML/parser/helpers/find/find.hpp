#pragma once

#include "../../../usings/usings.hpp"

namespace ieml {
	namespace detail {
		template<typename IteratorType>
		struct IsReverseIterator : std::false_type {};
		
		template<typename IteratorType>
		struct IsReverseIterator<std::reverse_iterator<IteratorType>> :
			std::integral_constant<bool, !IsReverseIterator<IteratorType>::value> {
		};
		
		template<typename IteratorType>
		static constexpr bool is_reverse_iterator_v = IsReverseIterator<IteratorType>::value;
	}
	
	template<typename IteratorType, typename ValueType>
	IteratorType find(IteratorType first, IteratorType last, const ValueType& value);
	
	template<typename IteratorType, typename ValueType>
	IteratorType rfind(IteratorType first, IteratorType last, const ValueType& value);
	
	template<typename ValueType, ValueType... Values, typename IteratorType>
	IteratorType find_set(IteratorType first, IteratorType last);
	
	template<typename ValueType, ValueType... Values, typename IteratorType>
	IteratorType rfind_set(IteratorType first, IteratorType last);
}

#include "find.inl"
