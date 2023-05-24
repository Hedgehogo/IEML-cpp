#include <ctre-unicode.hpp>
#include "../../parser/helpers/blankLines/blankLines.hpp"

namespace ieml {
	static constexpr auto reBoolValue = ctll::fixed_string{R"(yes|no)"};
	
	template<typename Char_>
	Option<bool> toBool(BasicStringCIter<Char_> first, BasicStringCIter<Char_> last) {
		if(auto boolValue{ctre::starts_with<reBoolValue>(first, last)}) {
			if(ctre::match<reBlankLine>(boolValue.end(), last)) {
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