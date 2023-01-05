#pragma once
#include "../node/Mark/Mark.hpp"
#include "../node/NodeData/INodeData.hpp"
#include "../reference/RefKeeper/RefKeeper.hpp"

namespace ieml {
	INodeData *parse(const std::string &config, Mark &mark, RefKeeper& refKeeper, const fs::path &filePath = {});
	
	INodeData *parse(const std::string &config, Mark &mark, const fs::path &filePath = {});
}
