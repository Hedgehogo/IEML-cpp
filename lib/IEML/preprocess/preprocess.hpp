#pragma once
#include <string>

namespace ieml {
	/// @brief Prepares the file for further processing, including deleting comments.
	///
	/// @param str String to be processed.
	///
	/// @return Processed string.
	std::string preprocess(const std::string &str);
}
