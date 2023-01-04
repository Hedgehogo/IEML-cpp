#include "parseScalar.hpp"
#include <algorithm>
#include <ctre/functions.hpp>
#include "../../../node/NodeData/scalar/ScalarNodeData.hpp"
#include "../../emptyLines/emptyLines.hpp"
#include "../../matchAndMove/matchAndMove.hpp"

namespace ieml {
	static constexpr auto string = ctll::fixed_string{ R"([^\"\n>]*?\n)" };
	static constexpr auto classicString = ctll::fixed_string{ R"(\"([^\"]|\\.)*?\")" };
	static constexpr auto unshieldedString = ctll::fixed_string{ R"(> .*?\n)" };
	static constexpr auto whitespace = ctll::fixed_string{ R"([\t ]*)" };
	
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
				}
				pos = find + 2;
			} else {
				str.append(pos, end);
				break;
			}
		}
		return str;
	}
	
	INodeData *parseScalar(Mark& mark, size_t indent, std::string::const_iterator& pos, std::string::const_iterator end) {
		if(auto classic = ctre::starts_with<classicString>(pos, end); classic) {
			pos = ctre::starts_with<emptyLine>(classic.end(), end).end();
			mark.line += std::count(classic.begin(), classic.end(), '\n') + 1;
			mark.symbol = 0;
			return new ScalarNodeData{handleClassicString(classic.begin() + 1, classic.end() - 1)};
		} else if(auto unshielded = matchAndEnter<unshieldedString>(mark, pos, end); unshielded) {
			std::string str{};
			while(unshielded) {
				str.append(unshielded.begin() + 2, unshielded.end());
				
				unshielded = ctre::starts_with<whitespace>(pos, end);
				unshielded = matchAndEnter<unshieldedString>(mark, unshielded.end(), pos, end);
			}
			str.pop_back();
			return new ScalarNodeData{str};
		} else if(auto general = matchAndEnter<string>(mark, pos, end); general) {
			return new ScalarNodeData{{general.begin(), general.end() - 1}};
		}
	}
}