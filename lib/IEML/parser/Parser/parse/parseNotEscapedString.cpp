#include "../Parser.hpp"
#include "../../helpers/match/match.hpp"
#include "../../helpers/whitespace/whitespace.hpp"

namespace ieml {
	static constexpr auto reNotEscapedString = ctll::fixed_string{R"(> [^\n]*)"};
	static constexpr auto reUnshieldedSpecial = ctll::fixed_string{R"(>>)"};
	static constexpr auto reLine = ctll::fixed_string{R"([^\n]*)"};
	
	bool matchNotEscaped(String::const_iterator& pos, String::const_iterator end, Mark& mark) {
		Mark currentMark{mark};
		String::const_iterator currentPos{pos};
		if(!matchAndMove<reUnshieldedSpecial>(currentPos, end, currentMark) ||
		   !matchAndMove<reWhitespace>(currentPos, end, currentMark) ||
		   pos == end || *pos == '\n') return false;
		
		mark = currentMark;
		pos = currentPos;
		return true;
	}
	
	bool matchTabs(String::const_iterator& pos, String::const_iterator end, Mark& mark, Size indent) {
		if(pos != end && *pos == '\n') {
			mark.enter(pos);
			Size currentIndent{0};
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
	
	Option<StringData> Parser::parseNotEscapedString(Size indent) {
		if(auto matched = matchAndMove<reNotEscapedString>(pos_, end(), mark_)) {
			StringData result{};
			Mark mark{mark_};
			String::const_iterator pos{matched.end()};
			while(matched) {
				result.append(matched.begin() + 2, matched.end());
				pos = matched.end();
				
				pos_ = pos;
				mark_ = mark;
				
				if(pos_ == end())
					break;
				
				mark.enter(pos);
				matched = ctre::starts_with<reWhitespace>(pos, end());
				matched = matchAndMove<reNotEscapedString>(matched.end(), pos, end(), mark);
				
				if(matched)
					result.push_back('\n');
			}
			return result;
		}
		if(matchNotEscaped(pos_, end(), mark_)) {
			StringData result{};
			Mark mark{mark_};
			String::const_iterator pos{pos_};
			while(matchTabs(pos, end(), mark, indent)) {
				auto line = matchAndMove<reLine>(pos, end(), mark);
				if(!result.empty()) result.push_back('\n');
				result.append(line.begin(), line.end());
				mark_ = mark;
				pos_ = pos;
			}
			return result;
		}
		return {};
	}
}