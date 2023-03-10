#pragma once

#include "../../node/Mark/Mark.hpp"
#include "../../node/NodeData/NodeData.hpp"
#include "../../reference/RefKeeper/RefKeeper.hpp"

namespace ieml {
	NodeData parseRef(std::string::const_iterator& pos, std::string::const_iterator end, const FilePath& filePath, RefKeeper& refKeeper, Mark& mark, size_t indent);
}
