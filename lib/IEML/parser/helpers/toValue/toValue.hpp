#pragma once

#include "toNumber/toNumber.hpp"
#include <string>
#include "../../../usings/usings.hpp"

namespace ieml {
	/// @brief Converts a letter into the bool.
	///
	/// @param first Beginning of a string containing a bool.
	/// @param last End of a string containing a bool.
	///
	/// @return bool The bool obtained from the string.
	///
	/// @note Does not check for correct input.
	bool toBool(String::const_iterator first, String::const_iterator last);
}
