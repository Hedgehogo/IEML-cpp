#pragma once
#include "../node/Mark/Mark.hpp"
#include "../node/NodeData/INodeData.hpp"

namespace ieml {
	INodeData *parse(const std::string &config, Mark &mark);
}
