#include "../Parser.hpp"
#include "../../helpers/emptyLines/emptyLines.hpp"
#include "../../helpers/match/match.hpp"
#include "../../helpers/tag/tag.hpp"

namespace ieml {
	static constexpr auto reMapKey = ctll::fixed_string{R"(([^\"\n<> ][^\"\n<>]*?|): ?)"};
	
	Option<MapData> Parser::parseMap(Size indent) {
		if(ctre::starts_with<reMapKey>(pos_, end())) {
			MapData nodes{};
			Mark currentMark{mark_};
			Size currentIndent{indent};
			String::const_iterator currentPos{pos_};
			while(currentIndent == indent) {
				if(auto find{matchAndMove<reMapKey>(currentPos, end(), currentMark)}) {
					pos_ = currentPos;
					mark_ = currentMark;
					
					String::const_iterator findEnd{find.end() - (*(find.end() - 1) == ' ' ? 2 : 1)};
					String str;
					NodeData nodeData;
					if(auto tagFind{ctre::search<reTagSpecial>(find.begin(), find.end())}) {
						str = {find.begin(), tagFind.begin()};
						String tagStr{tagFind.end(), findEnd};
						nodeData = TagData{parseAnchor(indent + 1), tagStr};
					} else {
						str = {find.begin(), findEnd};
						nodeData = parseAnchor(indent + 1);
					}
					nodes.emplace(str, PNode{Node{nodeData, currentMark}});
					
					currentPos = pos_;
					currentMark = mark_;
					
					if(pos_ != end() && *pos_ != '\n')
						except(FailedParseException::Reason::ExpectedMapKey);
					skipBlankLines(currentPos, end(), currentMark);
					currentIndent = matchAndMove<reTabs>(currentPos, end(), currentMark).size();
				} else if(currentPos == end()) {
					break;
				} else {
					except(FailedParseException::Reason::ExpectedMapKey);
				}
			}
			if(currentIndent > indent)
				except(FailedParseException::Reason::ExpectedMapKey);
			return nodes;
		}
		return {};
	}
}