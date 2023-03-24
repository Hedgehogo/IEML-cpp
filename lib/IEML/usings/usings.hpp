#pragma once
#include <optional>
#include "../helpers/fileSystem/fileSystem.hpp"

namespace ieml {
	template<typename T>
	using Option = std::optional<T>;
	using IStream = std::istream;
	using String = std::string;
	using Size = std::size_t;
}