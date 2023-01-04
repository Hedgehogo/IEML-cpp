#pragma once
#include <ctre/functions.hpp>
#include "../../node/Mark/Mark.hpp"

namespace ieml {
	static constexpr auto emptyLine = ctll::fixed_string{ R"([\t ]*\n)" };
	static constexpr auto tabs = ctll::fixed_string{ R"(\t*)" };
	
	void skipEmptyLines(Mark &mark, std::string::const_iterator &pos, std::string::const_iterator end);
}
