#pragma once
#include <ctre/functions.hpp>
#include "../../../../node/Mark/Mark.hpp"
#include "../../../../node/NodeData/INodeData.hpp"
#include "../../../../reference/RefKeeper/RefKeeper.hpp"

namespace ieml {
	static constexpr auto mapKey = ctll::fixed_string{ R"([^\"\n>]*?: ?)" };
	
	INodeData *parseMap(std::string::const_iterator &pos, std::string::const_iterator end, RefKeeper &refKeeper, Mark &mark, size_t indent);
}
