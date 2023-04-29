#include "blankLines.hpp"

namespace ieml {
	bool isEnter(String::const_iterator pos, String::const_iterator end) {
		return pos != end && *pos == '\n';
	}
	
	bool matchEnter(String::const_iterator& pos, String::const_iterator end, Mark& mark) {
		if(isEnter(pos, end)) {
			mark.enter(pos);
			return true;
		}
		return false;
	}
	
	bool matchIndent(String::const_iterator& pos, String::const_iterator end, Mark& mark, Size indent) {
		Size currentIndent{0};
		String::const_iterator currentPos{pos};
		while(currentIndent < indent && currentPos != end && *currentPos == '\t') {
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
	
	bool skipIndent(String::const_iterator& pos, String::const_iterator end, Mark& mark, Size indent) {
		if(auto tabs{ctre::starts_with<reIndent>(pos, end)}) {
			if(tabs.size() == indent) {
				mark.symbol += tabs.size();
				pos = tabs.end();
				return true;
			}
		}
		return false;
	}
	
	bool skipBlankLine(String::const_iterator& pos, String::const_iterator end, Mark& mark) {
		if(auto line{ctre::starts_with<reBlankLine>(pos, end)}) {
			mark.symbol += line.size();
			pos = line.end();
			return true;
		}
		return false;
	}
	
	bool skipBlankLinesLn(String::const_iterator& pos, String::const_iterator end, Mark& mark) {
		auto line{ctre::starts_with<reBlankLine>(pos, end)};
		if(line && isEnter(line.end(), end)) {
			do {
				pos = line.end() + 1;
				mark.enter();
				line = ctre::starts_with<reBlankLine>(line.end() + 1, end);
			} while(line && isEnter(line.end(), end));
			return true;
		}
		return false;
	}
}