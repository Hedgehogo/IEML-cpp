#pragma once
#include "../node/Mark/Mark.hpp"
#include "../node/Node/Node.hpp"
#include "../reference/RefKeeper/RefKeeper.hpp"

namespace ieml {
	NodeData parse(const std::string &config, Mark &mark, RefKeeper& refKeeper, const fs::path &filePath = {});
	
	NodeData parse(const std::string &config, Mark &mark, const fs::path &filePath = {});
}
