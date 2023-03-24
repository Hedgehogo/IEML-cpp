//included into getTypeName.hpp
#include <typeinfo>

namespace ieml {
	template <class T>
	String getTypeName(const T& type) {
		return detail::demangle(typeid(type).name());
	}
	
	template <class T>
	String getTypeName() {
		return detail::demangle(typeid(T).name());
	}
}