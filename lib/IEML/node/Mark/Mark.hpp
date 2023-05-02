#pragma once

#include <string>
#include "../../usings/usings.hpp"

namespace ieml {
	struct Mark {
		Size line;
		Size symbol;
		
		void enter();
		
		template<typename Char_ = Char>
		void enter(BasicStringCIter<Char_>& pos) {
			++pos;
			enter();
		}
	};
}
