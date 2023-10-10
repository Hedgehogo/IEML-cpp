#pragma once

#include <ctre-unicode.hpp>
#include "../../../node/Mark/Mark.hpp"

namespace ieml {
	static constexpr auto re_blank_line = ctll::fixed_string{R"([\t ]*(#[! ][^\n]*)?)"};
	static constexpr auto re_indent = ctll::fixed_string{R"(\t*)"};
	
	template<typename Char_ = Char>
	bool is_enter(BasicStringCIter<Char_> pos, BasicStringCIter<Char_> end);
	
	template<typename Char_ = Char>
	bool match_enter(BasicStringCIter<Char_>& pos, BasicStringCIter<Char_> end, Mark& mark);
	
	template<typename Char_ = Char>
	bool match_indent(BasicStringCIter<Char_>& pos, BasicStringCIter<Char_> end, Mark& mark, Size indent);
	
	template<typename Char_ = Char>
	bool skip_blank_line(BasicStringCIter<Char_>& pos, BasicStringCIter<Char_> end, Mark& mark);
	
	template<typename Char_ = Char>
	bool skip_blank_lines_ln(BasicStringCIter<Char_>& pos, BasicStringCIter<Char_> end, Mark& mark);
}

#include "blank_lines.inl"
