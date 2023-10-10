//included into ../Parser.hpp
#include "../../helpers/match/match.hpp"

namespace ieml {
	static constexpr auto re_line_string = ctll::fixed_string{R"(> ([^\n]*))"};
	
	template<typename Char_, typename FileInclude_>
	Option<BasicStringData<Char_>> BasicParser<Char_, FileInclude_>::parse_line_string() {
		if(auto find{match_and_move<re_line_string, Char_>(pos_, end(), mark_)}) {
			return {find.template get<1>().str()};
		}
		return {};
	}
}