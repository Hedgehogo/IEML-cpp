#pragma once

#include "../../../node/Mark/Mark.hpp"
#include "../../../node/Node/Node.hpp"
#include "../../../reference/RefKeeper/RefKeeper.hpp"

namespace ieml {
	NodeData parseShortList(std::string::const_iterator& pos, std::string::const_iterator end, const FilePath& filePath, RefKeeper& refKeeper, Mark& mark, size_t indent);
}
