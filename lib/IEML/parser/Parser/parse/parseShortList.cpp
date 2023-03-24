#include "../Parser.hpp"
#include "../../helpers/match/match.hpp"

namespace ieml {
	static constexpr auto special = ctll::fixed_string{R"([\[\]\"]|, ?)"};
	
	Option<ListData> Parser::parseShortList(Size indent) {
		// To do
	}
}