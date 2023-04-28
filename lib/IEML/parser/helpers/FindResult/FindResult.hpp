#pragma once

#include <ctre.hpp>

namespace ieml {
	namespace detail {
		static constexpr auto reFindResult = ctll::fixed_string{R"()"};
	}
	using FindResult = decltype(ctre::starts_with<detail::reFindResult>(std::declval<String::const_iterator>(), std::declval<String::const_iterator>()));
}
