#include "Mark.hpp"

namespace ieml {
	void Mark::enter() {
		symbol = 0;
		++line;
	}
}