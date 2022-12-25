#include "BaseException.hpp"

namespace ieml {
	BaseException::BaseException(std::string description) : description(description) {}
	
	std::string BaseException::getDescription() {
		return description;
	}
	
	const char *BaseException::what() const noexcept {
		return description.c_str();
	}
}