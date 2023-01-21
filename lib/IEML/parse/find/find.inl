//included into find.hpp
#include <algorithm>

namespace ieml {
	namespace detail {
		template <typename IteratorType, typename ValueType>
		IfNotReverseIterator<IteratorType> rfind(IteratorType first, IteratorType last, const ValueType &value) {
			return std::find(std::make_reverse_iterator(last), std::make_reverse_iterator(first), value).base();
		}
		
		template <typename IteratorType, typename ValueType>
		IfReverseIterator<IteratorType> rfind(IteratorType first, IteratorType last, const ValueType &value) {
			return std::make_reverse_iterator(std::find(last.base(), first.base(), value));
		}
	}
	
	template<typename IteratorType, typename ValueType>
	IteratorType find(IteratorType first, IteratorType last, const ValueType& value) {
		return std::find(first, last, value);
	}
	
	template<typename IteratorType, typename ValueType>
	IteratorType rfind(IteratorType first, IteratorType last, const ValueType& value) {
		return detail::rfind(first, last, value);
	}
}