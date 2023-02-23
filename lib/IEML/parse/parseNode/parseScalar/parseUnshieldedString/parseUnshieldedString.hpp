#pragma once
#include "../../../../node/Node/Node.hpp"
#include "../../../../node/Mark/Mark.hpp"
#include "../whitespace.hpp"

namespace ieml {
	Option<StringData> parseUnshieldedString(std::string::const_iterator &inputPos, std::string::const_iterator inputEnd, Mark &inputMark);
}
