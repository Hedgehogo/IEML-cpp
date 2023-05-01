//included into ../Parser.hpp
#include "../../helpers/blankLines/blankLines.hpp"
#include "../../helpers/match/match.hpp"

namespace ieml {
	template<typename Char_, typename FileInclude_>
	Option<NodeData> Parser<Char_, FileInclude_>::parseNotScalar(Size indent) {
		if(skipBlankLinesLn(pos_, end(), mark_)) {
			if(matchIndent(pos_, end(), mark_, indent)) {
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