#include "emptyLines.hpp"

namespace ieml {
	bool skipBlankLines(std::string::const_iterator& pos, std::string::const_iterator end, Mark& mark) {
		auto empty = ctre::starts_with<reBlankLine>(pos, end);
		if(!empty)
			return false;
		while(empty) {
			pos = empty.end();
			mark.enter();
			empty = ctre::starts_with<reBlankLine>(pos, end);
		}
		return true;
	}
}