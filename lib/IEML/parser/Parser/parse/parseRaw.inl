//included into ../Parser.hpp
#include "../../helpers/match/match.hpp"

namespace ieml {
	static constexpr auto reRaw = ctll::fixed_string{R"([^\"\n<>]+)"};
	
	template<typename Char_, typename FileInclude_>
	Option<RawData> Parser<Char_, FileInclude_>::parseRaw() {
		if(auto raw{matchAndMove<reRaw>(pos_, end(), mark_)}) {
			return RawData{String{raw.begin(), raw.end()}};
		}
		return {};
	}
}