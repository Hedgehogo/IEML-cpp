#pragma once
#include <ctre/functions.hpp>

namespace ieml {
	namespace detail {
		static constexpr auto findResultRegex = ctll::fixed_string{ R"()" };
	}
	using FindResult = decltype(ctre::starts_with<detail::findResultRegex>(std::declval<std::string::const_iterator>(), std::declval<std::string::const_iterator>()));
}
