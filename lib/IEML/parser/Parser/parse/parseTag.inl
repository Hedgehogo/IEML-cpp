//included into ../Parser.hpp
#include "../../helpers/match/match.hpp"
#include "../../helpers/tag/tag.hpp"

namespace ieml {
	template<typename Char_, typename FileInclude_>
	Option<TagData> Parser<Char_, FileInclude_>::parseTag(Size indent) {
		if(auto find{matchAndMove<reTag>(pos_, end(), mark_)}) {
			String tagStr{find.template get<1>().str()};
			return TagData{parseNode(indent), tagStr};
		} else {
			return {};
		}
	}
}