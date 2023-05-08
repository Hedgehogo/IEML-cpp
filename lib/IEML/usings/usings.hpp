#pragma once

#include <option_result.hpp>
#include "../helpers/fileSystem/fileSystem.hpp"

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
	
	using Char = char;
	using IStream = std::basic_istream<Char>;
	using String = BasicString<Char>;
	using Size = std::size_t;
}