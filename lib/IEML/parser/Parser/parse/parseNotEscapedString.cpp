#include "../Parser.hpp"
#include "../../helpers/match/match.hpp"
#include "../../helpers/blankLines/blankLines.hpp"

namespace ieml {
	static constexpr auto reNotEscapedString = ctll::fixed_string{R"(> ([^\n]*))"};
	static constexpr auto reNotEscapedSpecial = ctll::fixed_string{R"(>>)"};
	static constexpr auto reLine = ctll::fixed_string{R"([^\n]*)"};
	
	bool matchNotEscapedSpecial(String::const_iterator& pos, String::const_iterator end, Mark& mark) {
		Mark currentMark{mark};
		String::const_iterator currentPos{pos};
		if(!matchAndMove<reNotEscapedSpecial>(currentPos, end, currentMark) ||
		   !skipBlankLine(currentPos, end, currentMark) ||
		   pos == end || *pos == '\n') return false;
		
		mark = currentMark;
		pos = currentPos;
		return true;
	}
	
	bool matchEnterAndIndent(String::const_iterator& pos, String::const_iterator end, Mark& mark, Size indent) {
		if(isEnter(pos, end)) {
			String::const_iterator currentPos{pos + 1};
			Mark currentMark{mark.line + 1, 0};
			if(matchIndent(currentPos, end, currentMark, indent)) {
				pos = currentPos;
				mark = currentMark;
				return true;
			}
		}
		return false;
	}
	
	Option<StringData> Parser::parseNotEscapedString(Size indent) {
		if(auto find{matchAndMove<reNotEscapedString>(pos_, end(), mark_)}) {
			return find.get<1>().str();
		}
		if(matchNotEscapedSpecial(pos_, end(), mark_)) {
			StringData result{};
			PosInfo posInfo{getPosInfo()};
			while(matchEnterAndIndent(posInfo.pos, end(), posInfo.mark, indent)) {
				auto line = matchAndMove<reLine>(posInfo.pos, end(), posInfo.mark);
				if(!result.empty()) result.push_back('\n');
				result.append(line.begin(), line.end());
				setPosInfo(posInfo);
			}
			return result;
		}
		return {};
	}
}