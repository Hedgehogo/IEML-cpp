//included into getTypeName.hpp
#include <typeinfo>

namespace ieml {
	template<typename T>
	String TypeName<T>::get() {
		return detail::demangle(typeid(T).name());
	}
	
	template<typename T>
	String getTypeName() {
		return TypeName<T>::get();
	}
}