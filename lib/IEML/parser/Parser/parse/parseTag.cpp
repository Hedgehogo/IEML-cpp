#include "../Parser.hpp"
#include "../../helpers/match/match.hpp"
#include "../../helpers/tag/tag.hpp"

namespace ieml {
	NodeData Parser::parseTag(Size indent, bool lineBegin) {
		if(auto find{matchAndMove<reTag>(pos_, end(), mark_)}) {
			String tagStr{find.get<1>().str()};
			return TagData{parseAnchor(indent), tagStr};
		} else {
			return parseAnchor(indent);
		}
	}
}