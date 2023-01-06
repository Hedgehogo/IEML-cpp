#pragma once
#include <ctre/functions.hpp>
#include "../../../../node/Mark/Mark.hpp"
#include "../../../../node/NodeData/INodeData.hpp"
#include "../../../../reference/RefKeeper/RefKeeper.hpp"

namespace ieml {
	static constexpr auto reMapKey = ctll::fixed_string{R"([^\"\n<>]*?: ?)" };
	
	INodeData *parseMap(std::string::const_iterator &pos, std::string::const_iterator end, const fs::path &filePath, RefKeeper &refKeeper, Mark &mark, size_t indent);
}
