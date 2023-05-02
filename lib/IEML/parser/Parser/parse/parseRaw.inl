//included into ../Parser.hpp
#include "../../helpers/match/match.hpp"

namespace ieml {
	static constexpr auto reRaw = ctll::fixed_string{R"([^\"\n<>]+)"};
	
	template<typename Char_, typename FileInclude_>
	Option<BasicRawData<Char_>> BasicParser<Char_, FileInclude_>::parseRaw() {
		if(auto raw{matchAndMove<reRaw, Char_>(pos_, end(), mark_)}) {
			return BasicRawData<Char_>{BasicString<Char_>{raw.begin(), raw.end()}};
		}
		return {};
	}
}