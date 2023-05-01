#include "../Parser.hpp"
#include "../../helpers/blankLines/blankLines.hpp"
#include "../../helpers/match/match.hpp"
#include "../../helpers/tag/tag.hpp"

namespace ieml {
	static constexpr auto reMapKey = ctll::fixed_string{R"(([^\"\n<>]*?):( |(?=\n)))"};
	
	Option<MapData> Parser::parseMap(Size indent) {
		if(ctre::starts_with<reMapKey>(pos_, end())) {
			MapData nodes{};
			PosInfo posInfo{getPosInfo()};
			bool rightIndent{true};
			while(rightIndent) {
				if(posInfo.pos == end()) {
					break;
				} else if(*posInfo.pos == ' ') {
					std::string str{posInfo.pos, end()};
					except(FailedParseException::Reason::ImpermissibleSpace);
				} else if(*posInfo.pos == '\t') {
					except(FailedParseException::Reason::ImpermissibleTab);
				} else if(auto find{matchAndMove<reMapKey>(posInfo.pos, end(), posInfo.mark)}) {
					setPosInfo(posInfo);
					String keyStr{find.get<1>().str()};
					NodeData nodeData{parseNode(indent + 1)};
					nodes.emplace(keyStr, PNode{Node{nodeData, posInfo.mark}});
					posInfo = getPosInfo();
					
					if(pos_ != end() && *pos_ != '\n')
						except(FailedParseException::Reason::ExpectedMapKey);
					skipBlankLinesLn(posInfo.pos, end(), posInfo.mark);
					rightIndent = matchIndent(posInfo.pos, end(), posInfo.mark, indent);
				} else {
					except(FailedParseException::Reason::ExpectedMapKey);
				}
			}
			return nodes;
		}
		return {};
	}
}