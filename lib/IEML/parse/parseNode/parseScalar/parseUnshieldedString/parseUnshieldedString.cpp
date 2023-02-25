#include "parseUnshieldedString.hpp"
#include "../../../match/match.hpp"
#include "../../../emptyLines/emptyLines.hpp"

namespace ieml {
	static constexpr auto reUnshieldedString = ctll::fixed_string{R"(> [^\n]*)"};
	static constexpr auto reUnshieldedSpecial = ctll::fixed_string{R"(>>)"};
	static constexpr auto reLine = ctll::fixed_string{R"([^\n]*)"};
	
	bool matchUnshielded(std::string::const_iterator& pos, std::string::const_iterator end, Mark& mark) {
		Mark currentMark{mark};
		std::string::const_iterator currentPos{pos};
		if(!matchAndMove<reUnshieldedSpecial>(currentPos, end, currentMark) ||
		   !matchAndMove<reWhitespace>(currentPos, end, currentMark) ||
		   pos == end || *pos == '\n') return false;
		
		mark = currentMark;
		pos = currentPos;
		return true;
	}
	
	bool matchTabs(std::string::const_iterator& pos, std::string::const_iterator end, Mark& mark, size_t indent) {
		if(pos != end && *pos == '\n') {
			mark.enter(pos);
			std::size_t currentIndent{0};
			while(currentIndent != indent) {
				if(pos != end && *pos == '\t') {
					++currentIndent;
					++mark.symbol;
					++pos;
				} else return false;
			}
			return true;
		}
		return false;
	}
	
	Option<StringData> parseUnshieldedString(std::string::const_iterator& pos, std::string::const_iterator end, Mark& mark, size_t indent) {
		if(auto matched = matchAndMove<reUnshieldedString>(pos, end, mark)) {
			StringData result{};
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
			return result;
		}
		if(matchUnshielded(pos, end, mark)) {
			StringData result{};
			Mark currentMark{mark};
			std::string::const_iterator currentPos{pos};
			while(matchTabs(currentPos, end, currentMark, indent)) {
				auto line = matchAndMove<reLine>(currentPos, end, currentMark);
				if(!result.empty()) result.push_back('\n');
				result.append(line.begin(), line.end());
				mark = currentMark;
				pos = currentPos;
			}
			return result;
		}
		return {};
	}
}