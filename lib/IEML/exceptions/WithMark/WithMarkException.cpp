#include "WithMarkException.hpp"

namespace ieml {
	WithMarkException::WithMarkException(Mark mark, std::string description) :
		BaseException(std::to_string(mark.line) + std::string(":") + std::to_string(mark.symbol) + std::string(": ") + description), mark(mark) {}
	
	Mark WithMarkException::getMark() {
		return mark;
	}
}