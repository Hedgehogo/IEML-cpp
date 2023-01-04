#pragma once
#include "../../../node/Mark/Mark.hpp"
#include "../../../node/NodeData/INodeData.hpp"
#include "parseList/parseList.hpp"
#include "parseMap/parseMap.hpp"

namespace ieml {
	INodeData *parseNotScalar(Mark& mark, size_t indent, std::string::const_iterator& pos, std::string::const_iterator end);
}
