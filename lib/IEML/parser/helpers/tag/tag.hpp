#pragma once

#include <ctre-unicode.hpp>

namespace ieml {
	static constexpr auto re_tag = ctll::fixed_string{R"(= ([^\n]*?):( | ?(?=\n)))"};
}
