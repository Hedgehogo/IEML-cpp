#include <cstring>
#include "BaseException.hpp"

namespace ieml {
	std::string BaseException::getFullDescription() const {
		return getDescription();
	}
	
	const char* BaseException::what() const noexcept {
		std::string str{getFullDescription()};
		char* result{new char[str.size() + 1]{}};
		strcpy(result, str.c_str());
		return result;
	}
}