#include "preprocess.hpp"
#include <ctre/functions.hpp>
#include <algorithm>

namespace ieml {
	static constexpr auto rePreprocess = ctll::fixed_string{R"( #|\"|> |< )" };
	static constexpr auto reComment = ctll::fixed_string{R"( #.*?\n)" };
	static constexpr auto reClassicString = ctll::fixed_string{R"(\"([^\\]|\\.)*?\")" };
	static constexpr auto reUnshieldedString = ctll::fixed_string{R"(> .*?\n)" };
	static constexpr auto reFileString = ctll::fixed_string{R"(< .*?\n)" };
	
	std::string preprocess(const std::string &str) {
		std::string::const_iterator resultEnd{str.cbegin()};
		std::string result{};
		while(resultEnd != str.end()) {
			auto generalFind{ctre::search<rePreprocess>(resultEnd, str.cend())};
			if(generalFind) {
				std::string::const_iterator findBegin{generalFind.begin()};
				result.append(resultEnd, findBegin);
				if(*findBegin == ' ') {
					if(auto find = ctre::starts_with<reComment>(findBegin, str.cend()); find) {
						resultEnd = find.end();
						result.push_back('\n');
					} else {
						resultEnd = str.cend();
					}
				} else if(*findBegin == '>') {
					if(auto find = ctre::starts_with<reUnshieldedString>(findBegin, str.cend()); find) {
						resultEnd = find.end();
					} else {
						resultEnd = str.cend();
					}
					result.append(findBegin, resultEnd);
				} else if(*findBegin == '<') {
					if(auto find = ctre::starts_with<reFileString>(findBegin, str.cend()); find) {
						resultEnd = find.end();
					} else {
						resultEnd = str.cend();
					}
					result.append(findBegin, resultEnd);
				} else if(*findBegin == '\"') {
					if(auto find = ctre::starts_with<reClassicString>(findBegin, str.cend()); find) {
						resultEnd = find.end();
					} else {
						resultEnd = str.cend();
					}
					result.append(findBegin, resultEnd);
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