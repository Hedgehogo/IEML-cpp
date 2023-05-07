#pragma once

#include <string>

namespace ieml {
	template<typename T>
	std::basic_string<T> readFile(FilePath filePath);
}

#include "readFile.inl"
