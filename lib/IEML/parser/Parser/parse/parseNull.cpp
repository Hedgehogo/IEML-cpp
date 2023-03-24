#include "../Parser.hpp"
#include "../../helpers/match/match.hpp"

namespace ieml {
	static constexpr auto reNull = ctll::fixed_string{R"(null ?)"};
	
	Option<NullData> Parser::parseNull() {
		if(matchAndMove<reNull>(pos_, end(), mark_)) {
			return NullData{};
		}
		return {};
	}
}