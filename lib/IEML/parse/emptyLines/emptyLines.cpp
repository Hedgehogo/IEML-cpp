#include "emptyLines.hpp"

namespace ieml {
	bool skipEmptyLines(Mark &mark, std::basic_string<char, std::char_traits<char>, std::allocator<char>>::const_iterator &pos, std::string::const_iterator end) {
		auto empty = ctre::starts_with<reEmptyLine>(pos, end);
		if(!empty) return false;
		while(empty) {
			pos = empty.end();
			++mark.line;
			empty = ctre::starts_with<reEmptyLine>(pos, end);
		}
		return true;
	}
}