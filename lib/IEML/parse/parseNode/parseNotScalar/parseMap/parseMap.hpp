#pragma once
#include <ctre/functions.hpp>
#include "../../../../node/Mark/Mark.hpp"
#include "../../../../node/NodeData/INodeData.hpp"

namespace ieml {
	static constexpr auto mapKey = ctll::fixed_string{ R"([^\"\n>]*?: ?)" };
	
	INodeData *parseMap(Mark& mark, size_t indent, std::string::const_iterator& pos, std::string::const_iterator end);
}
