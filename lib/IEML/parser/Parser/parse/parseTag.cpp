#include "../Parser.hpp"
#include "../../helpers/match/match.hpp"
#include "../../helpers/tag/tag.hpp"

namespace ieml {
	NodeData Parser::parseTag(Size indent, bool lineBegin) {
		if(auto tagFind{matchAndMove<reTag>(pos_ + (lineBegin ? indent : 0), pos_, end(), mark_)}; tagFind) {
			int endIndent{*(tagFind.end() - 1) == ' ' ? 2 : 1};
			String tagStr{tagFind.begin() + 2, tagFind.end() - endIndent};
			return TagData{parseAnchor(indent + 1), tagStr};
		} else {
			return parseAnchor(indent + (lineBegin ? 0 : 1));
		}
	}
}