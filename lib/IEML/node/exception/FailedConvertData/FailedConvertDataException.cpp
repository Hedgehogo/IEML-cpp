#include "FailedConvertDataException.hpp"

namespace ieml {
	FailedConvertDataException::FailedConvertDataException(Mark mark, const TypeInfo& type_info) :
		WithMarkException(mark), type_info_(type_info) {
	}
	
	String FailedConvertDataException::get_description() const {
		return String("Failed to convert node to '") + get_type_name() + String("'");
	}
	
	String FailedConvertDataException::get_type_name() const {
		return type_info_.getName();
	}
	
	const TypeInfo& FailedConvertDataException::get_type_info() const {
		return type_info_;
	}
}