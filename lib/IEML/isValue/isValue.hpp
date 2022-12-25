#pragma once
#include <string>

namespace ieml {
	/// @brief Checks if the string Enter.
	///
	/// @param std::string::const_iterator Beginning of the string to be checked.
	/// @param std::string::const_iterator End of string to be checked.
	///
	/// @return Value whether the string Enter.
	bool isEnter(std::string::const_iterator first, std::string::const_iterator last);
	
	/// @brief Checks if the string File.
	///
	/// @param std::string::const_iterator Beginning of the string to be checked.
	/// @param std::string::const_iterator End of string to be checked.
	///
	/// @return Value whether the string File.
	bool isFile(std::string::const_iterator first, std::string::const_iterator last);
	
	/// @brief Checks if the string Null.
	///
	/// @param std::string::const_iterator Beginning of the string to be checked.
	/// @param std::string::const_iterator End of string to be checked.
	///
	/// @return Value whether the string Null.
	bool isNull(std::string::const_iterator first, std::string::const_iterator last);
	
	/// @brief Checks if the string Bool.
	///
	/// @param std::string::const_iterator Beginning of the string to be checked.
	/// @param std::string::const_iterator End of string to be checked.
	///
	/// @return Value whether the string Bool.
	bool isBool(std::string::const_iterator first, std::string::const_iterator last);
	
	/// @brief Checks if the string Double.
	///
	/// @param std::string::const_iterator Beginning of the string to be checked.
	/// @param std::string::const_iterator End of string to be checked.
	///
	/// @return Value whether the string Double.
	bool isDouble(std::string::const_iterator first, std::string::const_iterator last);
	
	/// @brief Checks if the string Int.
	///
	/// @param std::string::const_iterator Beginning of the string to be checked.
	/// @param std::string::const_iterator End of string to be checked.
	///
	/// @return Value whether the string Int.
	bool isInt(std::string::const_iterator first, std::string::const_iterator last);
}
