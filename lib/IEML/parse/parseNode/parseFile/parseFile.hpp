#pragma once
#include "../../../node/Mark/Mark.hpp"
#include "../../../node/NodeData/INodeData.hpp"
#include "../../../reference/RefKeeper/RefKeeper.hpp"

namespace ieml {
	INodeData *parseFile(std::string::const_iterator &pos, std::string::const_iterator end, RefKeeper &refKeeper, Mark &mark, size_t indent);
}
