#include "FailedConvertDataException.hpp"

namespace ieml {
	FailedConvertDataException::FailedConvertDataException(Mark mark, String type) :
		WithMarkException(mark), type(type) {
	}
	
	String FailedConvertDataException::getDescription() const {
		return String("Failed to convert node to '") + type + String("'");
	}
	
	String FailedConvertDataException::getType() const {
		return type;
	}
}