#pragma once

#include <option_result/option_result.hpp>
#include "../helpers/file_system/file_system.hpp"

namespace ieml {
	template<typename T>
	using Option = orl::Option<T>;
	template<typename T, typename E>
	using Result = orl::Result<T, E>;
	template<typename Char_>
	using BasicString = std::basic_string<Char_>;
	template<typename Char_>
	using BasicStringIter = typename BasicString<Char_>::iterator;
	template<typename Char_>
	using BasicStringCIter = typename BasicString<Char_>::const_iterator;
	template<typename Char_>
	using BasicStringView = std::basic_string_view<Char_>;
	
	using Char = char;
	using String = BasicString<Char>;
	using StringView = BasicStringView<Char>;
	using Size = std::size_t;
}