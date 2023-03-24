#pragma once

#include "ctre/functions.hpp"

namespace ieml {
	static constexpr auto reTagSpecial = ctll::fixed_string{R"( ?= )"};
	static constexpr auto reTag = ctll::fixed_string{R"( ?= [^\"\n<>]*?: ?)"};
}
