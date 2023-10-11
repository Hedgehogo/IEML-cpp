//included into find.hpp
#include <algorithm>

namespace ieml {
	template<typename IteratorType, typename ValueType>
	IteratorType find(IteratorType first, IteratorType last, const ValueType& value) {
		return std::find(first, last, value);
	}
	
	template<typename IteratorType, typename ValueType>
	IteratorType rfind(IteratorType first, IteratorType last, const ValueType& value) {
		if constexpr(!detail::is_reverse_iterator_v<IteratorType>) {
			return std::find(std::make_reverse_iterator(last), std::make_reverse_iterator(first), value).base() - 1;
		} else {
			return std::make_reverse_iterator(std::find(last.base(), first.base(), value)) - 1;
		}
	}
	
	namespace detail {
		template<typename ValueType>
		bool in_set(ValueType value) {
			return false;
		}
		
		template<typename ValueType, ValueType Value, ValueType... Values>
		bool in_set(ValueType value) {
			return value == Value || in_set<ValueType, Values...>(value);
		}
	}
	
	template<typename ValueType, ValueType... Values, typename IteratorType>
	IteratorType find_set(IteratorType first, IteratorType last) {
		return std::find_if(first, last, [](typename IteratorType::value_type value) {
			return detail::in_set<ValueType, Values...>(value);
		});
	}
	
	template<typename ValueType, ValueType... Values, typename IteratorType>
	IteratorType rfind_set(IteratorType first, IteratorType last) {
		if constexpr(!detail::is_reverse_iterator_v<IteratorType>) {
			return find_set<ValueType, Values...>(std::make_reverse_iterator(last), std::make_reverse_iterator(first)).base() - 1;
		} else {
			return std::make_reverse_iterator(find_set<ValueType, Values...>(last.base(), first.base())) - 1;
		}
	}
}