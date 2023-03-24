#pragma once
#include "../usings/usings.hpp"

namespace ieml {
	template<typename T>
	constexpr IStream::char_type toChar(T ch) {
		return static_cast<IStream::char_type>(ch);
	}
}
