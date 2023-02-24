#include "toValue.hpp"
#include <ctre/functions.hpp>

namespace ieml {
	static constexpr auto toBoolValue = ctll::fixed_string{R"((yes|true) *)"};
	
	bool toBool(std::string::const_iterator first, std::string::const_iterator last) {
		return ctre::match<toBoolValue>(first, last);
	}
}