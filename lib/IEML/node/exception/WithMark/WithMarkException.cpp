#include "WithMarkException.hpp"

namespace ieml {
	WithMarkException::WithMarkException(Mark mark) : mark_(mark) {
	}
	
	String WithMarkException::get_note() const {
		return std::to_string(mark_.line) + String(":") + std::to_string(mark_.symbol) + String(": ");
	}
	
	Mark WithMarkException::get_mark() {
		return mark_;
	}
}