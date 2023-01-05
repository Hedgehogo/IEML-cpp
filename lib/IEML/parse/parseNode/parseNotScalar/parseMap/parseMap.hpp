#pragma once
#include <ctre/functions.hpp>
#include "../../../../node/Mark/Mark.hpp"
#include "../../../../node/NodeData/INodeData.hpp"
#include "../../../../reference/RefKeeper/RefKeeper.hpp"

namespace ieml {
	static constexpr auto mapKey = ctll::fixed_string{ R"([^\"\n>]*?: ?)" };
	
	INodeData *
	parseMap(std::basic_string<char, std::char_traits<char>, std::allocator<char>>::const_iterator &pos, std::basic_string<char, std::char_traits<char>, std::allocator<char>>::const_iterator end, const fs::path &filePath, RefKeeper &refKeeper,
			 Mark &mark, size_t indent);
}
