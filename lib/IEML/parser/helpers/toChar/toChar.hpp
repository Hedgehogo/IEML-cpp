#pragma once
#include "../../../usings/usings.hpp"

namespace ieml {
	template<typename Char_>
	constexpr Char_ toChar(char ch) {
		return static_cast<Char_>(ch);
	}
}
