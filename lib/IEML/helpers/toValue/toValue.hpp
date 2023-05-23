#pragma once

#include "number/number_Parser.hpp"

namespace ieml {
	/// @brief Converts a string into the bool.
	///
	/// @param first Beginning of a string containing a bool.
	/// @param last End of a string containing a bool.
	///
	/// @tparam Char_ String character type.
	///
	/// @return bool The bool obtained from the string.
	template<typename Char_>
	Option<bool> toBool(BasicStringCIter<Char_> first, BasicStringCIter<Char_> last);
}

#include "toValue.inl"
