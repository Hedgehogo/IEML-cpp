#include "toNumber.hpp"
#include <string>

namespace ieml {
	int toDigit(char symbol) {
		if(symbol >= '0' && symbol <= '9') {
			return symbol - '0';
		} else if(symbol >= 'A' && symbol <= 'Z') {
			return symbol - 'A' + 10;
		} else if(symbol >= 'a' && symbol <= 'z') {
			return symbol - 'a' + 10;
		}
		return -1;
	}
	
	llint toIntFromBasis(std::string_view string) {
		int start{(string[0] == '-' || string[0] == '+') ? 3 : 2};
		int basis{string[start - 1] - 'a' + 1};
		llint number{toDigit(string[start])};
		for(std::string::size_type i = start + 1; i < string.size(); ++i) {
			number = number * basis + toDigit(string[i]);
		}
		if(string[0] == '-') {
			return -number;
		} else {
			return number;
		}
	}
	
	llint toIntFromDecimal(std::string_view string) {
		int start{(string[0] == '-' || string[0] == '+') ? 1 : 0};
		llint number{(string[start] - '0')};
		for(std::string::size_type i = start + 1; i < string.size(); ++i) {
			number = number * 10 + (string[i] - '0');
		}
		if(string[0] == '-') {
			return -number;
		} else {
			return number;
		}
	}
	
	llint toInt(std::string_view string) {
		int start{(string[0] == '-' || string[0] == '+') ? 1 : 0};
		if(string.size() > 1 && string[start] == '0' && string[start + 1] >= 'a') {
			return toIntFromBasis(string);
		} else {
			return toIntFromDecimal(string);
		}
	}
	
	double toDoubleFromBasis(std::string_view string) {
		int start{(string[0] == '-' || string[0] == '+') ? 3 : 2};
		int basis{string[start - 1] - 'a' + 1};
		double number{static_cast<double>(toDigit(string[start]))};
		int divider{1};
		bool divide{false};
		for(std::string::size_type i = start + 1; i < string.size(); ++i) {
			char symbol = string[i];
			if(divide) {
				divider *= basis;
			}
			if(symbol != '.') {
				number = number * basis + toDigit(string[i]);
			} else {
				divide = true;
			}
		}
		if(string[0] == '-') {
			return -number / divider;
		} else {
			return number / divider;
		}
	}
	
	double toDoubleFromDecimal(std::string_view string) {
		int start{(string[0] == '-' || string[0] == '+') ? 1 : 0};
		double number{static_cast<double>(string[start] - '0')};
		int divider{1};
		bool divide{false};
		for(std::string::size_type i = start + 1; i < string.size(); ++i) {
			char symbol = string[i];
			if(divide) {
				divider *= 10;
			}
			if(symbol != '.') {
				number = number * 10 + (string[i] - '0');
			} else {
				divide = true;
			}
		}
		if(string[0] == '-') {
			return -number / divider;
		} else {
			return number / divider;
		}
	}
	
	double toDouble(std::string_view string) {
		int start{(string[0] == '-' || string[0] == '+') ? 1 : 0};
		if(string.size() > 1 && string[start] == '0' && string[start + 1] >= 'a') {
			return toDoubleFromBasis(string);
		} else {
			return toDoubleFromDecimal(string);
		}
	}
}