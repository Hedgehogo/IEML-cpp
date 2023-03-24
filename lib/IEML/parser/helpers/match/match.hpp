#pragma once

#include "ctre/functions.hpp"
#include "../../../node/Mark/Mark.hpp"

namespace ieml {
	template <CTRE_REGEX_INPUT_TYPE regex>
	auto matchAndMove(String::const_iterator& pos, String::const_iterator end, Mark& mark) {
		auto find{ctre::starts_with<regex>(pos, end)};
		if(find) {
			pos = find.end();
			mark.symbol += find.size();
		}
		return find;
	}
	
	template <CTRE_REGEX_INPUT_TYPE regex>
	auto matchAndMove(String::const_iterator begin, String::const_iterator& pos, String::const_iterator end, Mark& mark) {
		auto find{ctre::starts_with<regex>(begin, end)};
		if(find) {
			pos = find.end();
			mark.symbol += find.size();
		}
		return find;
	}
}
