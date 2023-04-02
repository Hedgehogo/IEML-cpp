#include "isValue.hpp"
#include "ctre/functions.hpp"

namespace ieml {
	static constexpr auto shortList = ctll::fixed_string{R"(\[.*\] *)"};
	
	bool isShortList(String::const_iterator first, String::const_iterator last) {
		return ctre::match<shortList>(first, last);;
	}
	
	static constexpr auto file = ctll::fixed_string{R"(< .*)"};
	
	bool isFile(String::const_iterator first, String::const_iterator last) {
		return ctre::match<file>(first, last);
	}
	
	static constexpr auto nullValue = ctll::fixed_string{R"(null *)"};
	
	bool isNull(String::const_iterator first, String::const_iterator last) {
		return ctre::match<nullValue>(first, last);
	}
	
	static constexpr auto boolValue = ctll::fixed_string{R"((no|yes|true|false) *)"};
	
	bool isBool(String::const_iterator first, String::const_iterator last) {
		return ctre::match<boolValue>(first, last);
	}
	
	static constexpr auto doubleValue = ctll::fixed_string{R"([\+\-]?([0-9_]+\.[0-9_]*|0[a-z][0-9A-P_]+\.[0-9A-P_]*) *)"};
	
	bool isDouble(String::const_iterator first, String::const_iterator last) {
		return ctre::match<doubleValue>(first, last);
	}
	
	static constexpr auto intValue = ctll::fixed_string{R"([\+\-]?([0-9_]+|0[a-z][0-9A-P_]+) *)"};
	
	bool isInt(String::const_iterator first, String::const_iterator last) {
		return ctre::match<intValue>(first, last);
	}
}