//included into unstable_type_name.hpp
#include <typeinfo>
#include <type_traits>

#if defined(_MSC_VER)

namespace ieml {
	template<typename T>
	String unstable_type_name() {
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
	String unstable_type_name() {
		return detail::demangle(typeid(T).name());
	}
}

#endif
