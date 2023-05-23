#include "number_Parser.hpp"

namespace ieml::number {
	bool NumberPart::notEmpty() {
		return factor > 1;
	}
	
	bool NumberPart::correct() {
		return factor != 0;
	}
}