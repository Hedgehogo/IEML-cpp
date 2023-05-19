#pragma once

#include "../WithMark/WithMarkException.hpp"

namespace ieml {
	class NodeException : public WithMarkException {
	public:
		NodeException(Mark mark);
		
		virtual NodeException* clone() const = 0;
	};
}
