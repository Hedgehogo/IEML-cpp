#include "../Parser.hpp"
#include "../../helpers/match/match.hpp"

namespace ieml {
	static constexpr auto reRaw = ctll::fixed_string{R"([^\"\n<>]+)"};
	
	Option<RawData> Parser::parseRaw() {
		if(auto raw{matchAndMove<reRaw>(pos_, end(), mark_)}) {
			return RawData{String{raw.begin(), raw.end()}};
		}
		return {};
	}
}