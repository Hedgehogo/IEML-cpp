#pragma once
#include "../../node/Mark/Mark.hpp"
#include "../../node/Node/Node.hpp"
#include "../../reference/RefKeeper/RefKeeper.hpp"

namespace ieml {
	NodeData parseNode(std::string::const_iterator &pos, std::string::const_iterator end, const fs::path &filePath, RefKeeper &refKeeper, Mark &mark, size_t indent);
}
