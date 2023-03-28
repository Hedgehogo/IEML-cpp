#include "FailedConvertDataException.hpp"

namespace ieml {
	FailedConvertDataException::FailedConvertDataException(Mark mark, const TypeInfo& typeInfo) :
		WithMarkException(mark), typeInfo_(typeInfo) {
	}
	
	String FailedConvertDataException::getDescription() const {
		return String("Failed to convert node to '") + getTypeName() + String("'");
	}
	
	String FailedConvertDataException::getTypeName() const {
		return typeInfo_.getName();
	}
	
	const TypeInfo& FailedConvertDataException::getTypeInfo() const {
		return typeInfo_;
	}
}