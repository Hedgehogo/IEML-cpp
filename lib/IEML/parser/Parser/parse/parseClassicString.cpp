#include "../Parser.hpp"
#include "../../helpers//blankLines/blankLines.hpp"

namespace ieml {
	struct StringMark {
		String::const_iterator pos;
		Size lastLength{0};
		Size enterCount{0};
		Size realLength{0};
	};
	
	bool matchIndent(String::const_iterator& pos, String::const_iterator end, Size indent) {
		Size currentIndent{0};
		String::const_iterator currentPos{pos};
		while(currentIndent < indent && currentPos != end && *currentPos == '\t') {
			currentIndent += 1;
			currentPos += 1;
		}
		if(currentIndent == indent) {
			pos = currentPos - 1;
			return true;
		}
		return false;
	}
	
	Option<StringMark> isClassicString(String::const_iterator inputPos, String::const_iterator end, Size indent) {
		if(*inputPos != '\"')
			return {};
		
		StringMark mark{inputPos + 1, 1};
		while(true) {
			if(mark.pos == end) {
				return {};
			}
			if(*mark.pos == '\"') {
				break;
			}
			if(*mark.pos == '\\') {
				mark.pos += 1;
				if(mark.pos == end) {
					return {};
				}
				switch (*mark.pos) {
					case '\\':
					case '\"':
					case 't':
					case 'n':
						mark.realLength += 1;
						mark.lastLength += 2;
						break;
					case '\n':
						mark.enterCount += 1;
						mark.lastLength = 0;
						mark.pos += 1;
						if(!matchIndent(mark.pos, end, indent)) {
							return {};
						}
						break;
					default:
						mark.realLength += 2;
						mark.lastLength += 2;
						break;
				}
			} else if(*mark.pos == '\n') {
				mark.enterCount += 1;
				mark.realLength += 1;
				mark.lastLength = 0;
				mark.pos += 1;
				if(!matchIndent(mark.pos, end, indent)) {
					return {};
				}
			} else {
				mark.lastLength += 1;
				mark.realLength += 1;
			}
			mark.pos += 1;
		}
		mark.pos += 1;
		mark.lastLength += 1;
		
		return mark;
	}
	
	void handleSymbol(String::const_iterator& input, String::iterator& output, Size indent) {
		if(*input == '\\') {
			input += 1;
			if(*input != '\n') {
				switch(*input) {
					case  'n': *output = '\n'; break;
					case  't': *output = '\t'; break;
					case '\"': *output = '\"'; break;
					case '\\': *output = '\\'; break;
					default:
						*output = '\\';
						output += 1;
						*output = *input;
				}
				output += 1;
			}
		} else {
			*output = *input;
			output += 1;
		}
		if(*input == '\n') {
			input += 1 + indent;
		} else {
			input += 1;
		}
	}
	
	String handleClassicString(String::const_iterator first, String::const_iterator last, Size realLength, Size indent) {
		String result(realLength, '\0');
		for(auto pos = result.begin(); pos < result.end();) {
			handleSymbol(first, pos, indent);
		}
		return result;
	}
	
	Option<StringData> Parser::parseClassicString(Size indent) {
		if(auto stringMark{isClassicString(pos_, end(), indent)}) {
			String result{handleClassicString(pos_ + 1, stringMark->pos - 1, stringMark->realLength, indent)};
			pos_ = stringMark->pos;
			mark_.symbol = stringMark->lastLength;
			mark_.line += stringMark->enterCount;
			return StringData{result};
		}
		return {};
	}
}