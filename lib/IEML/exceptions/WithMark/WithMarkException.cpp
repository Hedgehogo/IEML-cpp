#include "WithMarkException.hpp"

namespace ieml {
	WithMarkException::WithMarkException(Mark mark) : mark(mark) {
	}
	
	std::string WithMarkException::getFullDescription() const {
		return std::to_string(mark.line) + std::string(":") + std::to_string(mark.symbol) + std::string(": ") + getDescription();
	}
	
	Mark WithMarkException::getMark() {
		return mark;
	}
}