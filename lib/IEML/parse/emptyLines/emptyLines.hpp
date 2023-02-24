#pragma once

#include <ctre/functions.hpp>
#include "../../node/Mark/Mark.hpp"

namespace ieml {
	static constexpr auto reEmptyLine = ctll::fixed_string{R"([\t ]*\n)"};
	static constexpr auto reCommentLine = ctll::fixed_string{R"([\t ]*([\t ]#[^\n]*)?)"};
	static constexpr auto reTabs = ctll::fixed_string{R"(\t*)"};
	
	bool skipEmptyLines(std::string::const_iterator &pos, std::string::const_iterator end, Mark &mark);
	
	bool skipEmptyLines(std::string::const_iterator &pos, std::string::const_iterator end, Mark &mark);
}
