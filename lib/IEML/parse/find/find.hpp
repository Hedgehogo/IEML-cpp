#pragma once

namespace ieml {
	namespace detail {
		template<typename IteratorType>
		struct IsReverseIterator : std::false_type {};
		
		template<typename IteratorType>
		struct IsReverseIterator<std::reverse_iterator<IteratorType>> :
			std::integral_constant<bool, !IsReverseIterator<IteratorType>::value> {};
		
		template<typename IteratorType>
		static constexpr bool isReverseIteratorV = IsReverseIterator<IteratorType>::value;
		
		template<typename IteratorType>
		using IfReverseIterator = std::enable_if_t<isReverseIteratorV<IteratorType>, IteratorType>;
		
		template<typename IteratorType>
		using IfNotReverseIterator = std::enable_if_t<!isReverseIteratorV<IteratorType>, IteratorType>;
		
		template<typename IteratorType, typename ValueType>
		IfNotReverseIterator<IteratorType> rfind(IteratorType first, IteratorType last, const ValueType& value);
		
		template<typename IteratorType, typename ValueType>
		IfReverseIterator<IteratorType> rfind(IteratorType first, IteratorType last, const ValueType& value);
	}
	
	template<typename IteratorType, typename ValueType>
	IteratorType find(IteratorType first, IteratorType last, const ValueType& value);
	
	template<typename IteratorType, typename ValueType>
	IteratorType rfind(IteratorType first, IteratorType last, const ValueType& value);
}

#include "find.inl"
