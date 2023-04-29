#pragma once

#include <ctre.hpp>

namespace ieml {
	static constexpr auto reTag = ctll::fixed_string{R"(= ([^\"\n<>]*?):( |(?=\n)))"};
}
