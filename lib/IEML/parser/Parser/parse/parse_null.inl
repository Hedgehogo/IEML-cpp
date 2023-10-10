//included into ../Parser.hpp
#include "../../helpers/match/match.hpp"

namespace ieml {
	static constexpr auto re_null = ctll::fixed_string{R"(null ?)"};
	
	template<typename Char_, typename FileInclude_>
	Option<NullData> BasicParser<Char_, FileInclude_>::parse_null() {
		if(match_and_move<re_null, Char_>(pos_, end(), mark_)) {
			return NullData{};
		}
		return {};
	}
}