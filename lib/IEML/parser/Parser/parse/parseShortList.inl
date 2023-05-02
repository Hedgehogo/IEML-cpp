//included into ../Parser.hpp
#include "../../helpers/match/match.hpp"

namespace ieml {
	static constexpr auto reShortListSpecial = ctll::fixed_string{R"([\[\]\"]|, ?)"};
	
	template<typename Char_, typename FileInclude_>
	Option<BasicListData<Char_>> BasicParser<Char_, FileInclude_>::parseShortList(Size indent) {
		// To do
	}
}