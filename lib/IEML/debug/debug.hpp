#pragma once

#include "../node/Node/Node.hpp"

namespace ieml {
	void debug(Node const& node, std::ostream& stream = std::cout, Size indentSize = 0);
}
