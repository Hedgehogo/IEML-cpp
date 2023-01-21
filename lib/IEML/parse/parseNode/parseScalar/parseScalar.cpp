#include "parseScalar.hpp"
#include <algorithm>
#include <ctre/functions.hpp>
#include "../../../node/NodeData/null/NullNodeData.hpp"
#include "../../../node/NodeData/scalar/ScalarNodeData.hpp"
#include "../../emptyLines/emptyLines.hpp"
#include "../../match/match.hpp"
#include "../../exceptions/FailedParseException.hpp"

namespace ieml {
	static constexpr auto reNull = ctll::fixed_string{R"(null ?)" };
	static constexpr auto reString = ctll::fixed_string{R"([^\"\n<>]*?\n)" };
	static constexpr auto reClassicString = ctll::fixed_string{R"(\"([^\"]|\\.)*?\")" };
	static constexpr auto reUnshieldedString = ctll::fixed_string{R"(> .*?\n)" };
	static constexpr auto reWhitespace = ctll::fixed_string{R"([\t ]*)" };
	
	std::string handleClassicString(std::string::const_iterator pos, std::string::const_iterator end) {
		std::string str{};
		while(pos != end) {
			auto find = std::find(pos, end, '\\');
			if(find != end) {
				str.append(pos, find);
				switch(find[1]) {
					case '"': str.push_back('\"'); break;
					case 'n': str.push_back('\n'); break;
					case 't': str.push_back('\t'); break;
					case '\\': str.push_back('\\'); break;
				}
				pos = find + 2;
			} else {
				str.append(pos, end);
				break;
			}
		}
		return str;
	}
	
	INodeData *parseScalar(std::string::const_iterator &pos, std::string::const_iterator end, const fs::path &filePath, Mark &mark, size_t indent) {
		if(auto null = matchAndMove<reNull>(mark, pos, end); null) {
			matchAndEnter<reEmptyLine>(mark, pos, end);
			return new NullNodeData{};
		}
		if(auto classic = ctre::starts_with<reClassicString>(pos, end); classic) {
			pos = ctre::starts_with<reEmptyLine>(classic.end(), end).end();
			mark.line += std::count(classic.begin(), classic.end(), '\n') + 1;
			mark.symbol = 0;
			return new ScalarNodeData{handleClassicString(classic.begin() + 1, classic.end() - 1)};
		}
		if(auto unshielded = matchAndEnter<reUnshieldedString>(mark, pos, end); unshielded) {
			std::string str{};
			while(unshielded) {
				str.append(unshielded.begin() + 2, unshielded.end());
				
				unshielded = ctre::starts_with<reWhitespace>(pos, end);
				unshielded = matchAndEnter<reUnshieldedString>(mark, unshielded.end(), pos, end);
			}
			str.pop_back();
			return new ScalarNodeData{str};
		}
		if(auto general = matchAndEnter<reString>(mark, pos, end); general) {
			return new ScalarNodeData{{general.begin(), general.end() - 1}};
		}
		throw FailedParseException{filePath, mark};
	}
}