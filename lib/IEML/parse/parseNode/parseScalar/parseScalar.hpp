#pragma once
#include "../../../node/Mark/Mark.hpp"
#include "../../../node/NodeData/INodeData.hpp"

namespace ieml {
	INodeData *parseScalar(std::string::const_iterator &pos, std::string::const_iterator end, Mark &mark, size_t indent);
}
