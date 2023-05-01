#include "../Parser.hpp"
#include "../../helpers/match/match.hpp"
#include "../../helpers/tag/tag.hpp"

namespace ieml {
	Option<TagData> Parser::parseTag(Size indent) {
		if(auto find{matchAndMove<reTag>(pos_, end(), mark_)}) {
			String tagStr{find.get<1>().str()};
			return TagData{parseNode(indent), tagStr};
		} else {
			return {};
		}
	}
}