#include "parseClassicString.hpp"
#include "../../../emptyLines/emptyLines.hpp"

namespace ieml {
	struct StringMark {
		std::string::const_iterator pos;
		std::size_t lastLength{0};
		std::size_t enterCount{0};
		std::size_t realLength{0};
	};
	
	Option<StringMark> isClassicString(std::string::const_iterator inputPos, std::string::const_iterator end) {
		if(*inputPos != '\"')
			return {};
		
		StringMark mark{inputPos + 1, 1};
		while(true) {
			if(mark.pos >= end)
				return {};
			if(*mark.pos == '\"')
				break;
			if(*mark.pos == '\\') {
				++mark.pos;
				if(*mark.pos != '\n') {
					mark.lastLength += 2;
					++mark.realLength;
				}
				++mark.pos;
			} else if(*mark.pos == '\n') {
				++mark.pos;
				++mark.enterCount;
				mark.lastLength = 0;
				++mark.realLength;
			} else {
				++mark.pos;
				++mark.lastLength;
				++mark.realLength;
			}
		}
		++mark.pos;
		++mark.lastLength;
		
		return mark;
	}
	
	void handleSymbol(std::string::const_iterator& input, std::string::iterator& output) {
		if(*input == '\\') {
			++input;
			if(*input != '\n') {
				if(*input == '"') {
					*output = '\"';
				} else if(*input == 'n') {
					*output = '\n';
				} else if(*input == 't') {
					*output = '\t';
				} else if(*input == '\\') {
					*output = '\\';
				} else {
					*output = '\\';
					++output;
					*output = *input;
				}
				++output;
			}
		} else {
			*output = *input;
			++output;
		}
		++input;
	}
	
	std::string handleClassicString(std::string::const_iterator first, std::string::const_iterator last, std::size_t realLength) {
		std::string result(realLength, '\0');
		for(auto pos = result.begin(); pos < result.end();) {
			handleSymbol(first, pos);
		}
		return result;
	}
	
	Option<StringData> parseClassicString(std::string::const_iterator& pos, std::string::const_iterator end, Mark& mark) {
		if(auto stringMark{isClassicString(pos, end)}) {
			std::string result{handleClassicString(pos + 1, stringMark->pos - 1, stringMark->realLength)};
			pos = stringMark->pos;
			mark.symbol = stringMark->lastLength;
			mark.line += stringMark->enterCount;
			return StringData{result};
		}
		return {};
	}
}