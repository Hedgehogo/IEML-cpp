//included into get_type_name.hpp
#include <typeinfo>
#include <type_traits>

#if defined(_MSC_VER)

namespace ieml {
	template<typename T>
	String TypeName<T>::get() {
		if constexpr(std::is_class_v<T>) {
			String name{detail::demangle(typeid(T).name())};
			std::string::const_iterator i{name.begin()};
			for(; (i != name.cend()) && (*i != ' '); ++i);
			return {++i, name.cend()};
		} else {
			return detail::demangle(typeid(T).name());
		}
	}
}

#else

namespace ieml {
	template<typename T>
	String TypeName<T>::get() {
		return detail::demangle(typeid(T).name());
	}
}

#endif

namespace ieml {
	template<typename T>
	String get_type_name() {
		return TypeName<T>::get();
	}
}
