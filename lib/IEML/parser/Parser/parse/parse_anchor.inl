//included into ../Parser.hpp
#include "../../helpers/match/match.hpp"
#include "../../helpers/blank_lines/blank_lines.hpp"

namespace ieml {
	static constexpr auto re_take_anchor = ctll::fixed_string{R"(&([^\n ]+)( | ?(?=\n)))"};
	static constexpr auto re_get_anchor = ctll::fixed_string{R"(\*([^\n ]+))"};
	
	template<typename Char_, typename FileInclude_>
	Option<BasicTakeAnchorData<Char_>> BasicParser<Char_, FileInclude_>::parse_take_anchor(Size indent) {
		Mark mark{mark_};
		if(auto find{match_and_move<re_take_anchor, Char_>(pos_, end(), mark_)}) {
			BasicString<Char_> name{find.template get<1>().str()};
			if(!anchor_keeper_->add(name, BasicNode<Char_>{parse_node(indent), mark}))
				throw FailedParseException{file_path_, FailedParseException::Reason::AnchorAlreadyExists, mark};
			return {BasicTakeAnchorData<Char_>{anchor_keeper_, name}};
		}
		return {};
	}
	
	template<typename Char_, typename FileInclude_>
	Option<BasicGetAnchorData<Char_>> BasicParser<Char_, FileInclude_>::parse_get_anchor(Size indent) {
		if(auto find{match_and_move<re_get_anchor, Char_>(pos_, end(), mark_)}) {
			BasicString<Char_> name{find.template get<1>().str()};
			
			skip_blank_line<Char_>(pos_, end(), mark_);
			return {BasicGetAnchorData < Char_ > {anchor_keeper_, name}};
		}
		return {};
	}
}