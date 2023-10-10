//included into ../Parser.hpp
#include "../../helpers/match/match.hpp"

namespace ieml {
	static constexpr auto re_raw = ctll::fixed_string{R"([^\"\n<>]+)"};
	
	template<typename Char_, typename FileInclude_>
	Option<BasicRawData<Char_>> BasicParser<Char_, FileInclude_>::parse_raw() {
		if(auto raw{match_and_move<re_raw, Char_>(pos_, end(), mark_)}) {
			return {BasicRawData<Char_>{raw.str()}};
		}
		return {};
	}
}