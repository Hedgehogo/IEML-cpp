#include "preprocess.hpp"
#include <ctre/functions.hpp>
#include <algorithm>

namespace ieml {
	static constexpr auto preprocessRegex = ctll::fixed_string{ R"(#|\"|> )" };
	static constexpr auto commentRegex = ctll::fixed_string{ R"(#.*?\n)" };
	static constexpr auto classicStringRegex = ctll::fixed_string{ R"(\"([^\\]|\\.)*?\")" };
	static constexpr auto unshieldedStringRegex = ctll::fixed_string{ R"(> .*?\n)" };
	
	std::string removeEnters(std::string::const_iterator begin, std::string::const_iterator end) {
		std::string result{};
		std::string::const_iterator findBegin{std::find(begin, end, '\n')};
		while(findBegin != end) {
			result.append(std::string{begin, findBegin} + "\\n");
			begin = findBegin + 1;
			findBegin = std::find(begin, end, '\n');
		}
		result.append(begin, end);
		return result;
	}
	
	std::string preprocess(std::string string) {
		std::string::const_iterator resultEnd{string.cbegin()};
		std::string result{};
		while(resultEnd != string.end()) {
			std::string::const_iterator findBegin{ctre::search<preprocessRegex>(resultEnd, string.cend()).begin()};
			result.append(resultEnd, findBegin);
			if(*findBegin == '#') {
				if(auto find = ctre::starts_with<commentRegex>(findBegin, string.cend()); find) {
					resultEnd = find.end();
					result.push_back('\n');
				} else {
					resultEnd = string.cend();
				}
			} else if(*findBegin == '>') {
				if(auto find = ctre::starts_with<unshieldedStringRegex>(findBegin, string.cend()); find) {
					resultEnd = find.end();
				} else {
					resultEnd = string.cend();
				}
				result.append(findBegin, resultEnd);
			} else if(*findBegin == '\"') {
				if(auto find = ctre::starts_with<classicStringRegex>(findBegin, string.cend()); find) {
					resultEnd = find.end();
				} else {
					resultEnd = string.cend();
				}
				result.append(removeEnters(findBegin, resultEnd));
			}
		}
		return result;
	}
}