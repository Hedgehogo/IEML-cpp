#pragma once

#include <ctre-unicode.hpp>
#include "../../../node/Mark/Mark.hpp"

namespace ieml {
	static constexpr auto reBlankLine = ctll::fixed_string{R"([\t ]*(#[! ][^\n]*)?)"};
	static constexpr auto reIndent = ctll::fixed_string{R"(\t*)"};
	
	template<typename Char_ = Char>
	bool isEnter(BasicStringCIter<Char_> pos, BasicStringCIter<Char_> end);
	
	template<typename Char_ = Char>
	bool matchEnter(BasicStringCIter<Char_>& pos, BasicStringCIter<Char_> end, Mark& mark);
	
	template<typename Char_ = Char>
	bool matchIndent(BasicStringCIter<Char_>& pos, BasicStringCIter<Char_> end, Mark& mark, Size indent);
	
	template<typename Char_ = Char>
	bool skipBlankLine(BasicStringCIter<Char_>& pos, BasicStringCIter<Char_> end, Mark& mark);
	
	template<typename Char_ = Char>
	bool skipBlankLinesLn(BasicStringCIter<Char_>& pos, BasicStringCIter<Char_> end, Mark& mark);
}

#include "blankLines.inl"
