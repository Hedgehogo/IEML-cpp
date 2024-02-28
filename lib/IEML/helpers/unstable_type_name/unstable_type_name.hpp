#pragma once

#include "TypeInfo/TypeInfo.hpp"

namespace ieml {
	namespace detail {
		String demangle(const char* name);
	}
	
	template<typename T>
	String unstable_type_name();
}

#include "unstable_type_name.inl"
