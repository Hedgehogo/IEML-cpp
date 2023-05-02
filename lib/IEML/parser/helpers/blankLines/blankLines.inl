//included into blankLines.hpp
#include "../toChar/toChar.hpp"

namespace ieml {
	template<typename Char_>
	bool isEnter(BasicStringCIter<Char_> pos, BasicStringCIter<Char_> end) {
		return pos != end && *pos == toChar<Char_>('\n');
	}
	
	template<typename Char_>
	bool matchEnter(BasicStringCIter<Char_>& pos, BasicStringCIter<Char_> end, Mark& mark) {
		if(isEnter<Char_>(pos, end)) {
			mark.enter<Char>(pos);
			return true;
		}
		return false;
	}
	
	template<typename Char_>
	bool matchIndent(BasicStringCIter<Char_>& pos, BasicStringCIter<Char_> end, Mark& mark, Size indent) {
		Size currentIndent{0};
		BasicStringCIter<Char_> currentPos{pos};
		while(currentIndent < indent && currentPos != end && *currentPos == toChar<Char_>('\t')) {
			currentIndent += 1;
			currentPos += 1;
		}
		if(currentIndent == indent) {
			pos = currentPos;
			mark.symbol += indent;
			return true;
		}
		return false;
	}
	
	template<typename Char_>
	bool skipBlankLine(BasicStringCIter<Char_>& pos, BasicStringCIter<Char_> end, Mark& mark) {
		if(auto line{ctre::starts_with<reBlankLine>(pos, end)}; line.end() != pos) {
			mark.symbol += line.size();
			pos = line.end();
			return true;
		}
		return false;
	}
	
	template<typename Char_>
	bool skipBlankLinesLn(BasicStringCIter<Char_>& pos, BasicStringCIter<Char_> end, Mark& mark) {
		auto line{ctre::starts_with<reBlankLine>(pos, end)};
		if(line && isEnter<Char_>(line.end(), end)) {
			do {
				pos = line.end() + 1;
				mark.enter();
				line = ctre::starts_with<reBlankLine>(line.end() + 1, end);
			} while(line && isEnter<Char_>(line.end(), end));
			return true;
		}
		return false;
	}
}