#pragma once
#include <string_view>

namespace ieml {
	using llint = long long;
	using uint = unsigned;
	using ulint = unsigned long;
	using ullint = unsigned long long;
	
	/// @brief Converts a letter into the corresponding number.
	///
	/// @param char Symbol.
	///
	/// @return int Number derived from the character:
	///   - [0-9] -> [0-9]
	///   - [A-Z] -> [10-36]
	///   - [a-z] -> [10-36]
	/// @note Does not check for correct input.
	int toDigit(char symbol);
	
	/// @brief Converts a string with a number with a specific number base to a number.
	///
	/// @param std::string_view String containing a number in the format (0[a-z][0-9A-Pa-p]+).
	///
	/// @return long long The number obtained from the string.
	///
	/// @note Does not check for correct input.
	llint toIntFromBasis(std::string_view string);
	
	/// @brief Converts a string with a number in decimal notation to a number.
	///
	/// @param std::string_view String containing a number in decimal notation.
	///
	/// @return long long The number obtained from the string.
	///
	/// @note Does not check for correct input.
	llint toIntFromDecimal(std::string_view string);
	
	/// @brief Converts a string with a number.
	///
	/// @param std::string_view String containing a number.
	///
	/// @return long long The number obtained from the string.
	///
	/// @note Does not check for correct input.
	llint toInt(std::string_view string);
	
	/// @brief Converts a string with a number with a specific number base to a number.
	///
	/// @param std::string_view String containing a number in the format (0[a-z][0-9A-Pa-p]+\.[0-9A-Pa-p]*).
	///
	/// @return double The number obtained from the string.
	///
	/// @note Does not check for correct input.
	double toDoubleFromBasis(std::string_view string);
	
	/// @brief Converts a string with a number in decimal notation to a number.
	///
	/// @param std::string_view String containing a number in decimal notation.
	///
	/// @return double The number obtained from the string.
	///
	/// @note Does not check for correct input.
	double toDoubleFromDecimal(std::string_view string);
	
	/// @brief Converts a string with a number.
	///
	/// @param std::string_view String containing a number.
	///
	/// @return double The number obtained from the string.
	///
	/// @note Does not check for correct input.
	double toDouble(std::string_view string);
}
