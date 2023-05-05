//included into ../Parser.hpp
#include "../../helpers/match/match.hpp"
#include "../../helpers/tag/tag.hpp"

namespace ieml {
	template<typename Char_, typename FileInclude_>
	Option<BasicTagData<Char_>> BasicParser<Char_, FileInclude_>::parseTag(Size indent) {
		Mark mark{mark_};
		if(auto find{matchAndMove<reTag, Char_>(pos_, end(), mark_)}) {
			BasicString<Char_> tagStr{find.template get<1>().str()};
			return BasicTagData<Char_>{BasicNode<Char_>{parseNode(indent), mark}, tagStr};
		} else {
			return {};
		}
	}
}