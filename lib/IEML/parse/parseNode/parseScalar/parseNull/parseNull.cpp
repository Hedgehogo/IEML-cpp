#include "parseNull.hpp"
#include "../../../match/match.hpp"

namespace ieml {
	static constexpr auto reNull = ctll::fixed_string{R"(null ?)"};
	
	Option<NullData> parseNull(std::basic_string<char, std::char_traits<char>, std::allocator<char>>::const_iterator& inputPos, std::string::const_iterator inputEnd, Mark& inputMark) {
		if(matchAndMove<reNull>(inputPos, inputEnd, inputMark)) {
			return NullData{};
		}
		return {};
	}
}