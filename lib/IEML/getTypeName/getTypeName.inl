//included into getTypeName.hpp
#include <typeinfo>

namespace ieml {
	template <class T>
	std::string getTypeName(const T& type) {
		return detail::demangle(typeid(type).name());
	}
	
	template <class T>
	std::string getTypeName() {
		return detail::demangle(typeid(T).name());
	}
}