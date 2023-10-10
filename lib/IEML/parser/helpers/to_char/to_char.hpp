#pragma once

#include "../../../usings/usings.hpp"

namespace ieml {
	template<typename Char_>
	constexpr Char_ to_char(char ch) {
		return static_cast<Char_>(ch);
	}
}
