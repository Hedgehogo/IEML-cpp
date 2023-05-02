//included into ../Parser.hpp
#include "../../helpers/match/match.hpp"
#include "../../helpers/tag/tag.hpp"

namespace ieml {
	template<typename Char_, typename FileInclude_>
	Option<BasicTagData<Char_>> BasicParser<Char_, FileInclude_>::parseTag(Size indent) {
		if(auto find{matchAndMove<reTag>(pos_, end(), mark_)}) {
			BasicString<Char_> tagStr{find.template get<1>().str()};
			return BasicTagData<Char_>{parseNode(indent), tagStr};
		} else {
			return {};
		}
	}
}