#include "../Parser.hpp"
#include "../../helpers//blankLines/blankLines.hpp"

namespace ieml {
	struct StringMark {
		String::const_iterator pos;
		Size lastLength{0};
		Size enterCount{0};
		Size realLength{0};
	};
	
	Option<StringMark> isClassicString(String::const_iterator inputPos, String::const_iterator end) {
		if(*inputPos != '\"')
			return {};
		
		StringMark mark{inputPos + 1, 1};
		while(true) {
			if(mark.pos == end)
				return {};
			if(*mark.pos == '\"')
				break;
			if(*mark.pos == '\\') {
				++mark.pos;
				if(mark.pos == end) {
					return {};
				}
				if(*mark.pos != '\n') {
					mark.lastLength += 2;
					++mark.realLength;
					if(*mark.pos != '\\' &&
					   *mark.pos != '\"' &&
					   *mark.pos != 't' &&
					   *mark.pos != 'n') {
						++mark.realLength;
					}
				} else {
					++mark.enterCount;
					mark.lastLength = 0;
				}
			} else if(*mark.pos == '\n') {
				++mark.enterCount;
				mark.lastLength = 0;
				++mark.realLength;
			} else {
				++mark.lastLength;
				++mark.realLength;
			}
			++mark.pos;
		}
		++mark.pos;
		++mark.lastLength;
		
		return mark;
	}
	
	void handleSymbol(String::const_iterator& input, String::iterator& output) {
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
	
	String handleClassicString(String::const_iterator first, String::const_iterator last, Size realLength) {
		String result(realLength, '\0');
		for(auto pos = result.begin(); pos < result.end();) {
			handleSymbol(first, pos);
		}
		return result;
	}
	
	Option<StringData> Parser::parseClassicString(Size indent) {
		if(auto stringMark{isClassicString(pos_, end())}) {
			String result{handleClassicString(pos_ + 1, stringMark->pos - 1, stringMark->realLength)};
			pos_ = stringMark->pos;
			mark_.symbol = stringMark->lastLength;
			mark_.line += stringMark->enterCount;
			return StringData{result};
		}
		return {};
	}
}