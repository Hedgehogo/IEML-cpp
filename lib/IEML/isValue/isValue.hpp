#pragma once
#include <string_view>

namespace ieml {
	/// @brief Checks if the string Enter.
	///
	/// @param std::string::const_iterator Beginning of the string to be checked.
	/// @param std::string::const_iterator End of string to be checked.
	///
	/// @return Value whether the string Enter.
	bool isEnter(std::string_view::const_iterator first, std::string_view::const_iterator last);
	
	/// @brief Checks if the string ShortList.
	///
	/// @param std::string::const_iterator Beginning of the string to be checked.
	/// @param std::string::const_iterator End of string to be checked.
	///
	/// @return Value whether the string ShortList.
	bool isShortList(std::string_view::const_iterator first, std::string_view::const_iterator last);
	
	/// @brief Checks if the string File.
	///
	/// @param std::string::const_iterator Beginning of the string to be checked.
	/// @param std::string::const_iterator End of string to be checked.
	///
	/// @return Value whether the string File.
	bool isFile(std::string_view::const_iterator first, std::string_view::const_iterator last);
	
	/// @brief Checks if the string Null.
	///
	/// @param std::string::const_iterator Beginning of the string to be checked.
	/// @param std::string::const_iterator End of string to be checked.
	///
	/// @return Value whether the string Null.
	bool isNull(std::string_view::const_iterator first, std::string_view::const_iterator last);
	
	/// @brief Checks if the string Bool.
	///
	/// @param std::string::const_iterator Beginning of the string to be checked.
	/// @param std::string::const_iterator End of string to be checked.
	///
	/// @return Value whether the string Bool.
	bool isBool(std::string_view::const_iterator first, std::string_view::const_iterator last);
	
	/// @brief Checks if the string Double.
	///
	/// @param std::string::const_iterator Beginning of the string to be checked.
	/// @param std::string::const_iterator End of string to be checked.
	///
	/// @return Value whether the string Double.
	bool isDouble(std::string_view::const_iterator first, std::string_view::const_iterator last);
	
	/// @brief Checks if the string Int.
	///
	/// @param std::string::const_iterator Beginning of the string to be checked.
	/// @param std::string::const_iterator End of string to be checked.
	///
	/// @return Value whether the string Int.
	bool isInt(std::string_view::const_iterator first, std::string_view::const_iterator last);
}
