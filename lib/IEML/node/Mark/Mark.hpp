#pragma once
#include <string>

namespace ieml {
	struct Mark {
		std::size_t line;
		std::size_t symbol;
		
		void enter();
		
		void enter(std::string::const_iterator &pos);
	};
}
