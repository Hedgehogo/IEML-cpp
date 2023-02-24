#pragma once

#include <string>

namespace ieml {
	namespace detail {
		std::string demangle(const char* name);
	}
	
	template <class T>
	std::string getTypeName(const T& type);
	
	template <class T>
	std::string getTypeName();
}

#include "getTypeName.inl"
