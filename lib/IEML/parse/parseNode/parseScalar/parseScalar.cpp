#include "parseScalar.hpp"
#include <algorithm>
#include <ctre/functions.hpp>
#include "../../../node/NodeData/null/NullNodeData.hpp"
#include "../../../node/NodeData/scalar/ScalarNodeData.hpp"
#include "../../emptyLines/emptyLines.hpp"
#include "../../matchAndMove/matchAndMove.hpp"
#include "../../exceptions/FailedParseException.hpp"

namespace ieml {
	static constexpr auto nullScalar = ctll::fixed_string{R"(null ?)" };
	static constexpr auto stringScalar = ctll::fixed_string{R"([^\"\n>]*?\n)" };
	static constexpr auto classicScalar = ctll::fixed_string{R"(\"([^\"]|\\.)*?\")" };
	static constexpr auto unshieldedScalar = ctll::fixed_string{R"(> .*?\n)" };
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
	
	INodeData *parseScalar(std::string::const_iterator &pos, std::string::const_iterator end, Mark &mark, size_t indent) {
		if(auto null = matchAndMove<nullScalar>(mark, pos, end); null) {
			matchAndEnter<emptyLine>(mark, pos, end);
			return new NullNodeData{};
		}
		if(auto classic = ctre::starts_with<classicScalar>(pos, end); classic) {
			pos = ctre::starts_with<emptyLine>(classic.end(), end).end();
			mark.line += std::count(classic.begin(), classic.end(), '\n') + 1;
			mark.symbol = 0;
			return new ScalarNodeData{handleClassicString(classic.begin() + 1, classic.end() - 1)};
		}
		if(auto unshielded = matchAndEnter<unshieldedScalar>(mark, pos, end); unshielded) {
			std::string str{};
			while(unshielded) {
				str.append(unshielded.begin() + 2, unshielded.end());
				
				unshielded = ctre::starts_with<whitespace>(pos, end);
				unshielded = matchAndEnter<unshieldedScalar>(mark, unshielded.end(), pos, end);
			}
			str.pop_back();
			return new ScalarNodeData{str};
		}
		if(auto general = matchAndEnter<stringScalar>(mark, pos, end); general) {
			return new ScalarNodeData{{general.begin(), general.end() - 1}};
		}
		throw FailedParseException{{}, mark};
	}
}