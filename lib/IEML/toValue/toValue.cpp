#include "toValue.hpp"
#include <ctre/functions.hpp>

namespace ieml {
	static constexpr auto toBoolValue = ctll::fixed_string{ R"((yes|true) *)" };
	
	bool toBool(std::string_view::const_iterator first, std::string_view::const_iterator last) {
		return ctre::match<toBoolValue>(first, last);
	}
}