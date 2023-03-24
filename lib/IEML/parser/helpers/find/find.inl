//included into find.hpp
#include <algorithm>

namespace ieml {
	namespace detail {
		template <typename IteratorType, typename ValueType>
		IfNotReverseIterator<IteratorType> rfind(IteratorType first, IteratorType last, const ValueType& value) {
			return std::find(std::make_reverse_iterator(last), std::make_reverse_iterator(first), value).base();
		}
		
		template <typename IteratorType, typename ValueType>
		IfReverseIterator<IteratorType> rfind(IteratorType first, IteratorType last, const ValueType& value) {
			return std::make_reverse_iterator(std::find(last.base(), first.base(), value));
		}
		
		template <typename IteratorType, typename ValueType, Size ValueSize>
		IteratorType findSet(IteratorType first, IteratorType last, const detail::Array<ValueType, ValueSize>& value) {
			return std::find_if(first, last, [&value](typename IteratorType::value_type item) {
				return std::find(std::begin(value), std::end(value), item) != std::end(value);
			});
		}
		
		template <typename IteratorType, typename ValueType, Size ValueSize>
		IfNotReverseIterator<IteratorType> rfindSet(IteratorType first, IteratorType last, const Array<ValueType, ValueSize>& value) {
			return findSet(std::make_reverse_iterator(last), std::make_reverse_iterator(first), value).base();
		}
		
		template <typename IteratorType, typename ValueType, Size ValueSize>
		IfReverseIterator<IteratorType> rfindSet(IteratorType first, IteratorType last, const Array<ValueType, ValueSize>& value) {
			return std::make_reverse_iterator(findSet(last.base(), first.base(), value));
		}
	}
	
	template <typename IteratorType, typename ValueType>
	IteratorType find(IteratorType first, IteratorType last, const ValueType& value) {
		return std::find(first, last, value);
	}
	
	template <typename IteratorType, typename ValueType>
	IteratorType rfind(IteratorType first, IteratorType last, const ValueType& value) {
		return detail::rfind(first, last, value);
	}
	
	template <typename IteratorType, typename ValueType, Size ValueSize>
	IteratorType findSet(IteratorType first, IteratorType last, const detail::Array<ValueType, ValueSize>& value) {
		return detail::findSet(first, last, value);
	}
	
	template <typename IteratorType, typename ValueType, Size ValueSize>
	IteratorType rfindSet(IteratorType first, IteratorType last, const detail::Array<ValueType, ValueSize>& value) {
		return detail::rfindSet(first, last, value);
	}
}