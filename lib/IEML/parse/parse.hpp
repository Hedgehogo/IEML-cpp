#pragma once

#include "../node/Mark/Mark.hpp"
#include "../node/Node/Node.hpp"
#include "../reference/RefKeeper/RefKeeper.hpp"

namespace ieml {
	NodeData parse(const std::string& config, Mark& mark, RefKeeper& refKeeper, const FilePath& filePath = {});
	
	NodeData parse(const std::string& config, Mark& mark, const FilePath& filePath = {});
}
