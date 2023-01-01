#include "toNumber.hpp"
#include <string>

namespace ieml {
	int toDigit(char symbol) {
		if(symbol >= '0' && symbol <= '9') {
			return symbol - '0';
		}
		if(symbol >= 'A' && symbol <= 'Z') {
			return symbol - 'A' + 10;
		}
		return -1;
	}
	
	llint toIntFromBasis(std::string_view::const_iterator first, std::string_view::const_iterator last) {
		std::string_view::const_iterator start{first + ((first[0] == '-' || first[0] == '+') ? 3 : 2)};
		int basis{*(start - 1) + 1 - 'a'};
		llint number{toDigit(*start)};
		for(std::string_view::const_iterator iter = start + 1; iter < last && *iter != ' '; ++iter) {
			number = number * basis + toDigit(*iter);
		}
		return (first[0] == '-' ? -number : number);
	}
	
	llint toIntFromDecimal(std::string_view::const_iterator first, std::string_view::const_iterator last) {
		std::string_view::const_iterator start{first + ((first[0] == '-' || first[0] == '+') ? 1 : 0)};
		llint number{start[0] - '0'};
		for(std::string_view::const_iterator iter = start + 1; iter < last && *iter != ' '; ++iter) {
			number = number * 10 + (*iter - '0');
		}
		return (first[0] == '-' ? -number : number);
	}
	
	llint toInt(std::string_view::const_iterator first, std::string_view::const_iterator last) {
		std::string_view::const_iterator start{first + ((first[0] == '-' || first[0] == '+') ? 1 : 0)};
		if(last > start + 1 && start[0] == '0' && start[1] >= 'a') {
			return toIntFromBasis(first, last);
		} else {
			return toIntFromBasis(first, last);
		}
	}
	
	double toDoubleFromBasis(std::string_view::const_iterator first, std::string_view::const_iterator last) {
		std::string_view::const_iterator start{first + ((first[0] == '-' || first[0] == '+') ? 3 : 2)};
		int basis{*(start - 1) + 1 - 'a'};
		double number{static_cast<double>(toDigit(*start))};
		int divider{1};
		bool divide{false};
		for(std::string_view::const_iterator iter = start + 1; iter < last && *iter != ' '; ++iter) {
			if(divide) divider *= basis;
			if(*iter != '.') {
				number = number * basis + toDigit(*iter);
			} else {
				divide = true;
			}
		}
		if(first[0] == '-') {
			return -number / divider;
		} else {
			return number / divider;
		}
	}
	
	double toDoubleFromDecimal(std::string_view::const_iterator first, std::string_view::const_iterator last) {
		std::string_view::const_iterator start{first + ((first[0] == '-' || first[0] == '+') ? 1 : 0)};
		double number{static_cast<double>(start[0] - '0')};
		int divider{1};
		bool divide{false};
		for(std::string_view::const_iterator iter = start + 1; iter < last && *iter != ' '; ++iter) {
			if(divide) divider *= 10;
			if(*iter != '.') {
				number = number * 10 + (*iter - '0');
			} else {
				divide = true;
			}
		}
		if(first[0] == '-') {
			return -number / divider;
		} else {
			return number / divider;
		}
	}
	
	double toDouble(std::string_view::const_iterator first, std::string_view::const_iterator last) {
		std::string_view::const_iterator start{first + ((first[0] == '-' || first[0] == '+') ? 1 : 0)};
		if(last > start + 1 && start[0] == '0' && start[1] >= 'a') {
			return toDoubleFromBasis(first, last);
		} else {
			return toDoubleFromDecimal(first, last);
		}
	}
}