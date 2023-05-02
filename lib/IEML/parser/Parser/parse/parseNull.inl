//included into ../Parser.hpp
#include "../../helpers/match/match.hpp"

namespace ieml {
	static constexpr auto reNull = ctll::fixed_string{R"(null ?)"};
	
	template<typename Char_, typename FileInclude_>
	Option<NullData> BasicParser<Char_, FileInclude_>::parseNull() {
		if(matchAndMove<reNull, Char_>(pos_, end(), mark_)) {
			return NullData{};
		}
		return {};
	}
}