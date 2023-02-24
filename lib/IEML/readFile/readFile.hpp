#pragma once

#include <string>

namespace ieml {
	template <typename T>
	std::basic_string<T> readFile(fs::path filePath);
}

#include "readFile.inl"
