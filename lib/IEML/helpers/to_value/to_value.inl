#include <ctre-unicode.hpp>
#include "../../parser/helpers/blank_lines/blank_lines.hpp"

namespace ieml {
	static constexpr auto re_bool_value = ctll::fixed_string{R"(yes|no)"};
	
	template<typename Char_>
	Option<bool> to_bool(BasicStringCIter<Char_> first, BasicStringCIter<Char_> last) {
		if(auto bool_value{ctre::starts_with<re_bool_value>(first, last)}) {
			if(ctre::match<re_blank_line>(bool_value.end(), last)) {
				if(*first == to_char<Char_>('y')) {
					return {true};
				} else {
					return {false};
				}
			}
		}
		return {};
	}
}