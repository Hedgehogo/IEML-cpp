//included into ../Parser.hpp
#include "../../helpers/match/match.hpp"
#include "../../helpers/blankLines/blankLines.hpp"

namespace ieml {
	static constexpr auto reNotEscapedString = ctll::fixed_string{R"(> ([^\n]*))"};
	static constexpr auto reNotEscapedSpecial = ctll::fixed_string{R"(>>)"};
	static constexpr auto reLine = ctll::fixed_string{R"([^\n]*)"};
	
	template<typename Char_>
	bool matchNotEscapedSpecial(BasicStringCIter<Char_>& pos, BasicStringCIter<Char_> end, Mark& mark) {
		Mark currentMark{mark};
		BasicStringCIter<Char_> currentPos{pos};
		if(!matchAndMove<reNotEscapedSpecial, Char_>(currentPos, end, currentMark))
			return false;
		skipBlankLine<Char_>(currentPos, end, currentMark);
		if(!isEnter<Char_>(currentPos, end))
			return false;
		
		mark = currentMark;
		pos = currentPos;
		return true;
	}
	
	template<typename Char_>
	bool matchEnterAndIndent(BasicStringCIter<Char_>& pos, BasicStringCIter<Char_> end, Mark& mark, Size indent) {
		if(isEnter<Char_>(pos, end)) {
			BasicStringCIter<Char_> currentPos{pos + 1};
			Mark currentMark{mark.line + 1, 0};
			if(matchIndent<Char_>(currentPos, end, currentMark, indent)) {
				pos = currentPos;
				mark = currentMark;
				return true;
			}
		}
		return false;
	}
	
	template<typename Char_, typename FileInclude_>
	Option<BasicStringData<Char_>> BasicParser<Char_, FileInclude_>::parseNotEscapedString(Size indent) {
		if(auto find{matchAndMove<reNotEscapedString, Char_>(pos_, end(), mark_)}) {
			return find.template get<1>().str();
		}
		if(matchNotEscapedSpecial<Char_>(pos_, end(), mark_)) {
			BasicStringData<Char_> result{};
			PosInfo posInfo{getPosInfo()};
			while(matchEnterAndIndent<Char_>(posInfo.pos, end(), posInfo.mark, indent)) {
				auto line = matchAndMove<reLine, Char_>(posInfo.pos, end(), posInfo.mark);
				if(!result.empty())
					result.push_back(toChar<Char_>('\n'));
				result.append(line.begin(), line.end());
				setPosInfo(posInfo);
			}
			return result;
		}
		return {};
	}
}