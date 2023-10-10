#pragma once

#include <string>

namespace ieml {
	template<typename T>
	std::basic_string<T> read_file(FilePath file_path);
}

#include "read_file.inl"
