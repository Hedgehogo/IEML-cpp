#pragma once

#include <ctre/functions.hpp>

namespace ieml {
	namespace detail {
		static constexpr auto reFindResult = ctll::fixed_string{R"()"};
	}
	using FindResult = decltype(ctre::starts_with<detail::reFindResult>(std::declval<std::string::const_iterator>(), std::declval<std::string::const_iterator>()));
}
