#include "emptyLines.hpp"

namespace ieml {
	bool skipEmptyLines(std::string::const_iterator& pos, std::string::const_iterator end, Mark& mark) {
		auto empty = ctre::starts_with<reEmptyLine>(pos, end);
		if(!empty)
			return false;
		while(empty) {
			pos = empty.end();
			++mark.line;
			empty = ctre::starts_with<reEmptyLine>(pos, end);
		}
		return true;
	}
}