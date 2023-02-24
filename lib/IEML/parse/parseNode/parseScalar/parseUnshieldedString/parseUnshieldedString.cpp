#include "parseUnshieldedString.hpp"
#include "../../../match/match.hpp"

namespace ieml {
	static constexpr auto reUnshieldedString = ctll::fixed_string{R"(> [^\n]*)"};
	
	Option<StringData> parseUnshieldedString(std::string::const_iterator& inputPos, std::string::const_iterator inputEnd, Mark& inputMark) {
		if(auto matched = matchAndMove<reUnshieldedString>(inputMark, inputPos, inputEnd); matched) {
			std::string result{};
			std::string::const_iterator pos{matched.end()};
			Mark mark{inputMark};
			while(matched) {
				result.append(matched.begin() + 2, matched.end());
				inputPos = matched.end();
				
				if(inputPos == inputEnd)
					break;
				
				mark.enter(pos);
				matched = ctre::starts_with<reWhitespace>(pos, inputEnd);
				matched = matchAndMove<reUnshieldedString>(mark, matched.end(), pos, inputEnd);
				
				if(matched)
					result.push_back('\n');
			}
			inputMark = mark;
			return StringData{result};
		}
		return {};
	}
}