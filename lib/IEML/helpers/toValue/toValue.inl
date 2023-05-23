#include <ctre-unicode.hpp>
#include "../../parser/helpers/blankLines/blankLines.hpp"

namespace ieml {
	static constexpr auto toBoolValue = ctll::fixed_string{R"([yes|no])"};
	
	template<typename Char_>
	Option<bool> toBool(BasicStringCIter<Char_> first, BasicStringCIter<Char_> last) {
		if(auto boolValue{ctre::starts_with<reBlankLine>(first, last)}) {
			if(ctre::starts_with<reBlankLine>(boolValue.end(), last).end() == last) {
				if(*first == toChar<Char_>('y')) {
					return {true};
				} else {
					return {false};
				}
			}
		}
		return {};
	}
}