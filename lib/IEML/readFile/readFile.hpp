#pragma once
#include <string>

namespace ieml {
	template<typename T>
	std::basic_string<T> readFile(std::string filePath);
}

#include "readFile.inl"
