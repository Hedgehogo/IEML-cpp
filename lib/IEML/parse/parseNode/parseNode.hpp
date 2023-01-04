#pragma once
#include "../../node/Mark/Mark.hpp"
#include "../../node/NodeData/INodeData.hpp"

namespace ieml {
	INodeData *parseNode(bool lineBegin, Mark& mark, size_t indent, std::string::const_iterator& pos, std::string::const_iterator end);
}
