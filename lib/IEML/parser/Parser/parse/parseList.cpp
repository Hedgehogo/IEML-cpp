#include "../Parser.hpp"
#include "../../helpers/blankLines/blankLines.hpp"
#include "../../helpers/match/match.hpp"

namespace ieml {
	static constexpr auto reListSpecial = ctll::fixed_string{R"(-[ \n])"};
	
	bool findListSpecial(String::const_iterator& pos, String::const_iterator end, Mark& mark) {
		bool find{matchAndMove<reListSpecial>(pos, end, mark)};
		if(*(pos - 1) == '\n') {
			--pos;
			--mark.symbol;
		}
		return find;
	}
	
	Option<ListData> Parser::parseList(Size indent) {
		if(ctre::starts_with<reListSpecial>(pos_, end())) {
			ListData nodes{};
			PosInfo posInfo{getPosInfo()};
			bool rightIndent{true};
			while(rightIndent) {
				if(findListSpecial(posInfo.pos, end(), posInfo.mark)) {
					setPosInfo(posInfo);
					NodeData nodeData{parseTag(indent, false)};
					nodes.emplace_back(std::move(Node{nodeData, posInfo.mark}));
					posInfo = getPosInfo();
					
					if(pos_ != end() && *pos_ != '\n')
						except(FailedParseException::Reason::ExpectedListItem);
					skipBlankLinesLn(posInfo.pos, end(), posInfo.mark);
					rightIndent = matchIndent(posInfo.pos, end(), posInfo.mark, indent);
				} else if(posInfo.pos == end()) {
					break;
				} else if(*posInfo.pos == ' ') {
					except(FailedParseException::Reason::ImpermissibleSpace);
				} else if(*posInfo.pos == '\t') {
					except(FailedParseException::Reason::ImpermissibleTab);
				} else {
					except(FailedParseException::Reason::ExpectedListItem);
				}
			}
			return nodes;
		}
		return {};
	}
}