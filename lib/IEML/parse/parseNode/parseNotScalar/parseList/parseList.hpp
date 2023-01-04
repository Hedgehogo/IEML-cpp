#pragma once
#include <ctre/functions.hpp>
#include "../../../../node/Mark/Mark.hpp"
#include "../../../../node/NodeData/INodeData.hpp"
#include "../../../../reference/RefKeeper/RefKeeper.hpp"

namespace ieml {
	static constexpr auto listSpecial = ctll::fixed_string{ R"(- ?)" };
	
	INodeData *parseList(std::string::const_iterator &pos, std::string::const_iterator end, RefKeeper &refKeeper, Mark &mark, size_t indent);
}
