#pragma once

#include "../../../../node/Node/Node.hpp"
#include "../../../../node/Mark/Mark.hpp"
#include "../whitespace.hpp"

namespace ieml {
	Option<StringData> parseClassicString(std::string::const_iterator& pos, std::string::const_iterator end, Mark& mark);
}
