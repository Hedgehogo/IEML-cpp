#include "parseRaw.hpp"
#include "../../../match/match.hpp"

namespace ieml {
	static constexpr auto reRaw = ctll::fixed_string{R"([^\"\n<>]*)" };
	
	Option<RawData> parseRaw(std::string::const_iterator &inputPos, std::string::const_iterator inputEnd, Mark &inputMark) {
		if(auto raw{matchAndMove<reRaw>(inputMark, inputPos, inputEnd)}) {
			return RawData{std::string{raw.begin(), raw.end()}};
		}
		return {};
	}
}