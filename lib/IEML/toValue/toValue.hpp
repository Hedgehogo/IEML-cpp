#pragma once
#include "toNumber/toNumber.hpp"
#include <string>

namespace ieml {
	bool toBool(std::string_view::const_iterator first, std::string_view::const_iterator last);
}
