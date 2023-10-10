#pragma once

#include "TypeInfo/TypeInfo.hpp"

namespace ieml {
	namespace detail {
		String demangle(const char* name);
	}
	
	template<typename T>
	struct TypeName {
		static String get();
	};
	
	template<typename T>
	String get_type_name();
}

#include "get_type_name.inl"
