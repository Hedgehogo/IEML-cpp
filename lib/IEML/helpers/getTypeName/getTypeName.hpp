#pragma once

#include <string>
#include "../../usings/usings.hpp"

namespace ieml {
	namespace detail {
		String demangle(const char* name);
	}
	
	template <class T>
	String getTypeName(const T& type);
	
	template <class T>
	String getTypeName();
}

#include "getTypeName.inl"
