#pragma once
#include <ctre/functions.hpp>
#include "../../node/Mark/Mark.hpp"
#include "../../node/Node/Node.hpp"
#include "../../reference/RefKeeper/RefKeeper.hpp"

namespace ieml {
	static constexpr auto reTagSpecial = ctll::fixed_string{R"( ?= )" };
	static constexpr auto reTag = ctll::fixed_string{R"( ?= [^\"\n<>]*?: ?)" };
	
	NodeData parseTag(std::string::const_iterator &pos, std::string::const_iterator end, const fs::path &filePath, RefKeeper &refKeeper, Mark &mark, size_t indent, bool lineBegin);
}
