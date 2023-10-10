#include "NumberParser.hpp"

namespace ieml::number {
	bool NumberPart::not_empty() {
		return factor > 1;
	}
	
	bool NumberPart::correct() {
		return factor != 0;
	}
}