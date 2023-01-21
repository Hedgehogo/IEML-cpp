#pragma once
#include "../../../node/Mark/Mark.hpp"
#include "../../../node/NodeData/INodeData.hpp"
#include "../../../reference/RefKeeper/RefKeeper.hpp"

namespace ieml {
	INodeData *parseShortList(std::string::const_iterator &pos, std::string::const_iterator end, const fs::path &filePath, RefKeeper &refKeeper, Mark &mark, size_t indent);
}
