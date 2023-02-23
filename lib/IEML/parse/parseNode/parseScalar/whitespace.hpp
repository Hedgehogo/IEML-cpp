#pragma once
#include <optional>
#include <ctre/functions.hpp>

namespace ieml {
	template<typename T>
	using Option = std::optional<T>;
	
	static constexpr auto reWhitespace = ctll::fixed_string{R"([\t ]*)" };
}
