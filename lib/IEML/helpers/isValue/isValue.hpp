#pragma once

#include "../../usings/usings.hpp"

namespace ieml {
	/// @brief Checks if the string ShortList.
	///
	/// @param first Beginning of the string to be checked.
	/// @param last End of string to be checked.
	///
	/// @return Value whether the string ShortList.
	bool isShortList(String::const_iterator first, String::const_iterator last);
	
	/// @brief Checks if the string File.
	///
	/// @param first Beginning of the string to be checked.
	/// @param last End of string to be checked.
	///
	/// @return Value whether the string File.
	bool isFile(String::const_iterator first, String::const_iterator last);
	
	/// @brief Checks if the string Null.
	///
	/// @param first Beginning of the string to be checked.
	/// @param last End of string to be checked.
	///
	/// @return Value whether the string Null.
	bool isNull(String::const_iterator first, String::const_iterator last);
	
	/// @brief Checks if the string Bool.
	///
	/// @param first Beginning of the string to be checked.
	/// @param last End of string to be checked.
	///
	/// @return Value whether the string Bool.
	bool isBool(String::const_iterator first, String::const_iterator last);
	
	/// @brief Checks if the string Double.
	///
	/// @param first Beginning of the string to be checked.
	/// @param last End of string to be checked.
	///
	/// @return Value whether the string Double.
	bool isDouble(String::const_iterator first, String::const_iterator last);
	
	/// @brief Checks if the string Int.
	///
	/// @param first Beginning of the string to be checked.
	/// @param last End of string to be checked.
	///
	/// @return Value whether the string Int.
	bool isInt(String::const_iterator first, String::const_iterator last);
}
