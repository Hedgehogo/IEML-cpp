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
		if(*inputPos != '\"') return {};
		
		StringMark mark{inputPos + 1, 1};
		while(true) {
			if(mark.pos >= end) return {};
			if(*mark.pos == '\"') break;
			if(*mark.pos == '\\') {
				mark.pos += 2;
				mark.lastLength += 2;
			} else if(*mark.pos == '\n') {
				++mark.pos;
				++mark.enterCount;
				mark.lastLength = 0;
			} else {
				++mark.pos;
				++mark.lastLength;
			}
			++mark.realLength;
		}
		++mark.pos;
		++mark.lastLength;
		
		return mark;
	}
	
	std::string handleClassicString(std::string::const_iterator first, std::string::const_iterator last, std::size_t realLength) {
		std::string result(realLength, '\0');
		for(auto pos = result.begin(); pos < result.end(); ++pos) {
			if(*first == '\\') {
				++first;
				switch(*first) {
					case '"': *pos = '\"'; break;
					case 'n': *pos = '\n'; break;
					case 't': *pos = '\t'; break;
					case '\\': *pos = '\\'; break;
					default:
						*pos = '\\';
						++pos;
						*pos = *first;
						break;
				}
			} else {
				*pos = *first;
			}
			++first;
		}
		return result;
	}
	
	Option<StringData> parseClassicString(std::string::const_iterator &pos, std::string::const_iterator end, Mark &mark) {
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