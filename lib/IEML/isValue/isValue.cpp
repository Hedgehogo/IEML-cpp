#include "isValue.hpp"
#include <ctre/functions.hpp>

namespace ieml {
	static constexpr auto enter = ctll::fixed_string{ R"( *)" };
	
	bool isEnter(std::string::const_iterator first, std::string::const_iterator last) {
		return ctre::match<enter>(first, last);
	}
	
	static constexpr auto shortList = ctll::fixed_string{ R"(\[.*\] *)" };
	
	bool isShortList(std::string::const_iterator first, std::string::const_iterator last) {
		return ctre::match<shortList>(first, last);;
	}
	
	static constexpr auto file = ctll::fixed_string{ R"(< .*)" };
	
	bool isFile(std::string::const_iterator first, std::string::const_iterator last) {
		return ctre::match<file>(first, last);
	}
	
	static constexpr auto nullValue = ctll::fixed_string{ R"(null *)" };
	
	bool isNull(std::string::const_iterator first, std::string::const_iterator last) {
		return ctre::match<nullValue>(first, last);
	}
	
	static constexpr auto boolValue = ctll::fixed_string{ R"((no|yes|true|false) *)" };
	
	bool isBool(std::string::const_iterator first, std::string::const_iterator last) {
		return ctre::match<boolValue>(first, last);
	}
	
	static constexpr auto doubleValue = ctll::fixed_string{ R"(([0-9]+\.[0-9]*|0[a-z][0-9A-P]+\.[0-9A-P]*) *)" };
	
	bool isDouble(std::string::const_iterator first, std::string::const_iterator last) {
		return ctre::match<doubleValue>(first, last);
	}
	
	static constexpr auto intValue = ctll::fixed_string{ R"(([0-9]+|0[a-z][0-9A-P]+) *)" };
	
	bool isInt(std::string::const_iterator first, std::string::const_iterator last) {
		return ctre::match<intValue>(first, last);
	}
}