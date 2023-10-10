#include "FailedDecodeDataException.hpp"

namespace ieml {
	FailedDecodeDataException::FailedDecodeDataException(Mark mark, const TypeInfo& type_info, BoxPtr<NodeException> reason) :
		NodeException(mark), type_info_(type_info), reason_(std::move(reason)) {
	}
	
	FailedDecodeDataException::FailedDecodeDataException(const FailedDecodeDataException& other) :
		NodeException(other.get_mark()), type_info_(other.type_info_), reason_(other.reason_->clone()) {
	}
	
	String FailedDecodeDataException::get_description() const {
		if(has_reason()) {
			return String("Failed to convert node to '") + get_type_name() + String("', because: \n") + reason_->get_full_description();
		}
		return String("Failed to convert node to '") + get_type_name() + String("'");
	}
	
	String FailedDecodeDataException::get_type_name() const {
		return type_info_.get_name();
	}
	
	bool FailedDecodeDataException::has_reason() const {
		return reason_.get() != nullptr;
	}
	
	const TypeInfo& FailedDecodeDataException::get_type_info() const {
		return type_info_;
	}
	
	Option<const NodeException&> FailedDecodeDataException::get_reason() const {
		if(reason_.get() != nullptr) {
			return Option<const NodeException&>{*reason_};
		}
		return Option<const NodeException&>{};
	}
	
	FailedDecodeDataException* FailedDecodeDataException::clone() const {
		return new FailedDecodeDataException{*this};
	}
}