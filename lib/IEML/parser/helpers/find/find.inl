//included into find.hpp
#include <algorithm>

namespace ieml {
	template<typename IteratorType, typename ValueType>
	IteratorType find(IteratorType first, IteratorType last, const ValueType& value) {
		return std::find(first, last, value);
	}
	
	template<typename IteratorType, typename ValueType>
	IteratorType rfind(IteratorType first, IteratorType last, const ValueType& value) {
		if constexpr(!detail::isReverseIteratorV<IteratorType>) {
			return std::find(std::make_reverse_iterator(last), std::make_reverse_iterator(first), value).base() - 1;
		} else {
			return std::make_reverse_iterator(std::find(last.base(), first.base(), value)) - 1;
		}
	}
	
	namespace detail {
		template<typename ValueType>
		bool inSet(ValueType value) {
			return false;
		}
		
		template<typename ValueType, ValueType Value, ValueType... Values>
		bool inSet(ValueType value) {
			return value == Value || inSet<ValueType, Values...>(value);
		}
	}
	
	template<typename ValueType, ValueType... Values, typename IteratorType>
	IteratorType findSet(IteratorType first, IteratorType last) {
		return std::find_if(first, last, [](typename IteratorType::value_type value) {
			return detail::inSet<ValueType, Values...>(value);
		});
	}
	
	template<typename ValueType, ValueType... Values, typename IteratorType>
	IteratorType rfindSet(IteratorType first, IteratorType last) {
		if constexpr(!detail::isReverseIteratorV<IteratorType>) {
			return findSet<ValueType, Values...>(std::make_reverse_iterator(last), std::make_reverse_iterator(first)).base() - 1;
		} else {
			return std::make_reverse_iterator(findSet<ValueType, Values...>(last.base(), first.base())) - 1;
		}
	}
}