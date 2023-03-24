#include <cstring>
#include "BaseException.hpp"
#include <ostream>

namespace ieml {
	String BaseException::getFullDescription() const {
		return getDescription();
	}
	
	const char* BaseException::what() const noexcept {
		String str{getFullDescription()};
		char* result{new char[str.size() + 1]{}};
		strcpy(result, str.c_str());
		return result;
	}
	
	std::ostream& operator<<(std::ostream& stream, const BaseException& exception) {
		stream << exception.getFullDescription();
		return stream;
	}
}