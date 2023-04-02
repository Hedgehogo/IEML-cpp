#pragma once
#include "../../../usings/usings.hpp"

namespace ieml {
	using llint = long long;
	using uint = unsigned;
	using ulint = unsigned long;
	using ullint = unsigned long long;
	
	/// @brief Converts a letter into the corresponding number.
	///
	/// @param char Symbol.
	///
	/// @return int Number derived from the character: \n
	///   - [0-9] -> [0-9] \n
	///   - [A-P] -> [10-25]
	///
	/// @note Does not check for correct input.
	int toDigit(char symbol);
	
	/// @brief Converts a string with a number with a specific number base to a number.
	///
	/// @param first Beginning of a string containing an integer in the format (0[a-z][0-9A-P]+).
	/// @param last End of a string containing an integer in the format (0[a-z][0-9A-P]+).
	///
	/// @return long long The number obtained from the string.
	///
	/// @note Does not check for correct input.
	llint toIntFromBasis(String::const_iterator first, String::const_iterator last);
	
	/// @brief Converts a string with a number in decimal notation to a number.
	///
	/// @param first Beginning of a string containing an integer in decimal notation.
	/// @param last End of a string containing an integer in decimal notation.
	///
	/// @return long long The number obtained from the string.
	///
	/// @note Does not check for correct input.
	llint toIntFromDecimal(String::const_iterator first, String::const_iterator last);
	
	/// @brief Converts a string with a number.
	///
	/// @param first Beginning of a string containing an integer.
	/// @param last End of a string containing an integer.
	///
	/// @return long long The number obtained from the string.
	///
	/// @note Does not check for correct input.
	llint toInt(String::const_iterator first, String::const_iterator last);
	
	/// @brief Converts a string with a number with a specific number base to a number.
	///
	/// @param first Beginning of a string containing a number in the format (0[a-z][0-9A-P]+\.[0-9A-P]*).
	/// @param last End of a string containing a number in the format (0[a-z][0-9A-P]+\.[0-9A-P]*).
	///
	/// @return double The number obtained from the string.
	///
	/// @note Does not check for correct input.
	double toDoubleFromBasis(String::const_iterator first, String::const_iterator last);
	
	/// @brief Converts a string with a number in decimal notation to a number.
	///
	/// @param first Beginning of a string containing a number in decimal notation.
	/// @param last End of a string containing a number in decimal notation.
	///
	/// @return double The number obtained from the string.
	///
	/// @note Does not check for correct input.
	double toDoubleFromDecimal(String::const_iterator first, String::const_iterator last);
	
	/// @brief Converts a string with a number.
	///
	/// @param first Beginning of a string containing a number.
	/// @param last End of a string containing a number.
	///
	/// @return double The number obtained from the string.
	///
	/// @note Does not check for correct input.
	double toDouble(String::const_iterator first, String::const_iterator last);
}
