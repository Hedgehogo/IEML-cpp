#include "FailedConvertDataException.hpp"

namespace ieml {
	FailedConvertDataException::FailedConvertDataException(Mark mark, std::string type) :
		WithMarkException(mark), type(type) {
	}
	
	std::string FailedConvertDataException::getDescription() const {
		return std::string("Failed to convert node to '") + type + std::string("'");
	}
	
	std::string FailedConvertDataException::getType() const {
		return type;
	}
}