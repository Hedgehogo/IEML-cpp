#pragma once

#include <string>
#include "../../usings/usings.hpp"

namespace ieml {
	struct Mark {
		Size line;
		Size symbol;
		
		void enter();
		
		void enter(String::const_iterator& pos);
	};
}
