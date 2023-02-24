#pragma once

#include "../../../node/Mark/Mark.hpp"
#include "../../../node/Node/Node.hpp"

namespace ieml {
	NodeData parseScalar(std::string::const_iterator& pos, std::string::const_iterator end, const fs::path& filePath, Mark& mark, size_t indent);
}
