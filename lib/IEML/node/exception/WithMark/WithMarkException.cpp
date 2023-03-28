#include "WithMarkException.hpp"

namespace ieml {
	WithMarkException::WithMarkException(Mark mark) : mark(mark) {
	}
	
	String WithMarkException::getFullDescription() const {
		return std::to_string(mark.line) + String(":") + std::to_string(mark.symbol) + String(": ") + getDescription();
	}
	
	Mark WithMarkException::getMark() {
		return mark;
	}
}