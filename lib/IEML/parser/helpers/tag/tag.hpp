#pragma once

#include <ctre-unicode.hpp>

namespace ieml {
	static constexpr auto reTag = ctll::fixed_string{R"(= ([^\n]*?):( | ?(?=\n)))"};
}
