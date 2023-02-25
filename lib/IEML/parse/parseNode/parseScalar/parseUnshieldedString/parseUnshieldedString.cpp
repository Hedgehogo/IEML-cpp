#include "parseUnshieldedString.hpp"
#include "../../../match/match.hpp"

namespace ieml {
	static constexpr auto reUnshieldedString = ctll::fixed_string{R"(> [^\n]*)"};
	
	Option<StringData> parseUnshieldedString(std::string::const_iterator& pos, std::string::const_iterator end, Mark& mark) {
		if(auto matched = matchAndMove<reUnshieldedString>(pos, end, mark); matched) {
			std::string result{};
			Mark currentMark{mark};
			std::string::const_iterator currentPos{matched.end()};
			while(matched) {
				result.append(matched.begin() + 2, matched.end());
				currentPos = matched.end();
				
				pos = currentPos;
				mark = currentMark;
				
				if(pos == end)
					break;
				
				currentMark.enter(currentPos);
				matched = ctre::starts_with<reWhitespace>(currentPos, end);
				matched = matchAndMove<reUnshieldedString>(matched.end(), currentPos, end, currentMark);
				
				if(matched)
					result.push_back('\n');
			}
			return StringData{result};
		}
		return {};
	}
}