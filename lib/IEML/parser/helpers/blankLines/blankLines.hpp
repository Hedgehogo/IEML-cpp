#pragma once

#include <ctre-unicode.hpp>
#include "../../../node/Mark/Mark.hpp"

namespace ieml {
	static constexpr auto reBlankLine = ctll::fixed_string{R"([\t ]*(#[! ][^\n]*)?)"};
	static constexpr auto reIndent = ctll::fixed_string{R"(\t*)"};
	
	bool isEnter(String::const_iterator pos, String::const_iterator end);
	
	bool matchEnter(String::const_iterator& pos, String::const_iterator end, Mark& mark);
	
	bool matchIndent(String::const_iterator& pos, String::const_iterator end, Mark& mark, Size indent);
	
	bool skipBlankLine(String::const_iterator& pos, String::const_iterator end, Mark& mark);
	
	bool skipBlankLinesLn(String::const_iterator& pos, String::const_iterator end, Mark& mark);
}
