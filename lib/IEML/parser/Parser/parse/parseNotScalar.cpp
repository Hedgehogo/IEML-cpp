#include "../Parser.hpp"
#include "../../helpers/emptyLines/emptyLines.hpp"
#include "../../helpers/match/match.hpp"

namespace ieml {
	Option<NodeData> Parser::parseNotScalar(Size indent) {
		if(skipBlankLines(pos_, end(), mark_)) {
			Size currentIndent{matchAndMove<reTabs>(pos_, end(), mark_)};
			if(currentIndent == indent) {
				if(auto list{parseList(indent)}) {
					return list.value();
				}
				if(auto map{parseMap(indent)}) {
					return map.value();
				}
			}
			exceptWithCheckSpace(FailedParseException::Reason::ExpectedNotScalar);
		}
		return {};
	}
}