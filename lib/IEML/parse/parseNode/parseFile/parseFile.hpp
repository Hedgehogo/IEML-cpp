#pragma once

#include "../../../node/Mark/Mark.hpp"
#include "../../../node/NodeData/NodeData.hpp"
#include "../../../reference/RefKeeper/RefKeeper.hpp"
#include "../parseScalar/whitespace.hpp"

namespace ieml {
	Option<FileData> parseFile(std::string::const_iterator& pos, std::string::const_iterator end, const fs::path& filePath, RefKeeper& refKeeper, Mark& mark, size_t indent);
}
