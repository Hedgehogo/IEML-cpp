#pragma once
#include <string_view>

namespace ieml {
	using llint = long long;
	using uint = unsigned;
	using ulint = unsigned long;
	using ullint = unsigned long long;
	
	int toDigit(char symbol);
	
	llint toIntFromBasis(std::string_view string);
	
	llint toIntFromDecimal(std::string_view string);
	
	llint toInt(std::string_view string);
	
	double toDoubleFromBasis(std::string_view string);
	
	double toDoubleFromDecimal(std::string_view string);
	
	double toDouble(std::string_view string);
	
	bool toBool(std::string_view string);
}
