#pragma once
#include "../../../node/Mark/Mark.hpp"
#include "../../../node/NodeData/INodeData.hpp"
#include "parseList/parseList.hpp"
#include "parseMap/parseMap.hpp"
#include "../../../reference/RefKeeper/RefKeeper.hpp"

namespace ieml {
	INodeData *parseNotScalar(std::string::const_iterator &pos, std::string::const_iterator end, RefKeeper &refKeeper, Mark &mark, size_t indent);
}
