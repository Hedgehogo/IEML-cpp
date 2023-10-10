//included into ../Parser.hpp
#include "../../helpers/match/match.hpp"
#include "../../helpers/tag/tag.hpp"

namespace ieml {
	template<typename Char_, typename FileInclude_>
	Option<BasicTagData<Char_>> BasicParser<Char_, FileInclude_>::parse_tag(Size indent) {
		Mark mark{mark_};
		if(auto find{match_and_move<re_tag, Char_>(pos_, end(), mark_)}) {
			BasicString<Char_> tag_str{find.template get<1>().str()};
			return {BasicTagData<Char_>{BasicNode<Char_>{parse_node(indent), mark}, tag_str}};
		} else {
			return {};
		}
	}
}