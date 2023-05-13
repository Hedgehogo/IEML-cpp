//included into ../Parser.hpp
#include "../../helpers/match/match.hpp"

namespace ieml {
	static constexpr auto reLineString = ctll::fixed_string{R"(> ([^\n]*))"};
	
	template<typename Char_, typename FileInclude_>
	Option<BasicStringData<Char_>> BasicParser<Char_, FileInclude_>::parseLineString() {
		if(auto find{matchAndMove<reLineString, Char_>(pos_, end(), mark_)}) {
			return {find.template get<1>().str()};
		}
		return {};
	}
}