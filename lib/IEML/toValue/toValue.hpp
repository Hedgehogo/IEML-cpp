#pragma once

#include "toNumber/toNumber.hpp"
#include <string>

namespace ieml {
	/// @brief Converts a letter into the bool.
	///
	/// @param first Beginning of a string containing a bool.
	/// @param last End of a string containing a bool.
	///
	/// @return bool The bool obtained from the string.
	///
	/// @note Does not check for correct input.
	bool toBool(std::string::const_iterator first, std::string::const_iterator last);
}
