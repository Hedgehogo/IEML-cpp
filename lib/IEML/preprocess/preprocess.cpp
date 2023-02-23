#include "preprocess.hpp"
#include <ctre/functions.hpp>
#include <algorithm>

namespace ieml {
	static constexpr auto rePreprocess = ctll::fixed_string{R"((^|[ \t\n])#|\"|> |< )" };
	static constexpr auto reComment = ctll::fixed_string{R"(#.*?\n)" };
	static constexpr auto reClassicString = ctll::fixed_string{R"(\"([^\\]|\\.)*?\")" };
	static constexpr auto reUnshieldedString = ctll::fixed_string{R"(> .*?\n)" };
	static constexpr auto reFileString = ctll::fixed_string{R"(< .*?\n)" };
	
	template<CTRE_REGEX_INPUT_TYPE R, typename T>
	inline void pasteIf(const std::string &str, std::string &result, std::string::const_iterator &resultEnd, T &findBegin) {
		if(auto find = ctre::starts_with<R>(findBegin, str.cend()); find) {
			resultEnd = find.end();
		} else {
			resultEnd = str.cend();
		}
		result.append(findBegin, resultEnd);
	}
	
	std::string preprocess(const std::string &str) {
		std::string::const_iterator resultEnd{str.cbegin()};
		std::string result{};
		while(resultEnd != str.end()) {
			auto generalFind{ctre::search<rePreprocess>(resultEnd, str.cend())};
			if(generalFind) {
				std::string::const_iterator findBegin{generalFind.begin()};
				result.append(resultEnd, findBegin);
				
				if(*findBegin == '>') {
					pasteIf<reUnshieldedString>(str, result, resultEnd, findBegin);
				} else if(*findBegin == '<') {
					pasteIf<reFileString>(str, result, resultEnd, findBegin);
				} else if(*findBegin == '\"') {
					pasteIf<reClassicString>(str, result, resultEnd, findBegin);
				} else if(*findBegin == '#' || *(findBegin + 1) == '#') {
					if(auto find = ctre::starts_with<reComment>(findBegin + (*findBegin == '#' ? 0 : 1), str.cend()); find) {
						resultEnd = find.end();
						result.push_back('\n');
					} else {
						resultEnd = str.cend();
					}
				}
			} else {
				result.append(resultEnd, str.cend());
				resultEnd = str.cend();
			}
		}
		result.push_back('\n');
		return result;
	}
}