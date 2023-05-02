#include "toValue.hpp"
#include <ctre-unicode.hpp>

namespace ieml {
	static constexpr auto toBoolValue = ctll::fixed_string{R"(yes *)"};
	
	bool toBool(String::const_iterator first, String::const_iterator last) {
		return ctre::match<toBoolValue>(first, last);
	}
}