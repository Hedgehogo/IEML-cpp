#pragma once

#include "../../usings/usings.hpp"

namespace ieml {
	/// @brief Prepares the file for further processing, including deleting comments.
	///
	/// @param str String to be processed.
	///
	/// @return Processed string.
	String preprocess(const String& str);
}
