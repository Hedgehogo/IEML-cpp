#pragma once

#include <ctre-unicode.hpp>
#include "../../../node/Mark/Mark.hpp"

namespace ieml {
	template<CTRE_REGEX_INPUT_TYPE regex, typename Char_ = Char>
	auto matchAndMove(BasicStringCIter<Char_>& pos, BasicStringCIter<Char_> end, Mark& mark) {
		auto find{ctre::starts_with<regex>(pos, end)};
		if(find) {
			pos = find.end();
			mark.symbol += find.size();
		}
		return find;
	}
	
	template<CTRE_REGEX_INPUT_TYPE regex, typename Char_ = Char>
	auto matchAndMove(BasicStringCIter<Char_> begin, BasicStringCIter<Char_>& pos, BasicStringCIter<Char_> end, Mark& mark) {
		auto find{ctre::starts_with<regex>(begin, end)};
		if(find) {
			pos = find.end();
			mark.symbol += find.size();
		}
		return find;
	}
}
