#include "FailedDecodeDataException.hpp"

namespace ieml {
	FailedDecodeDataException::FailedDecodeDataException(Mark mark, TypeInfo const& type_info, BoxPtr<NodeException> reason) :
		NodeException(mark), type_info_(type_info), reason_(std::move(reason)) {
	}
	
	FailedDecodeDataException::FailedDecodeDataException(FailedDecodeDataException const& other) :
		NodeException(other.get_mark()),
		type_info_(other.type_info_),
		reason_(other.reason_.get() != nullptr ? other.reason_->clone() : nullptr) {
	}
	
	String FailedDecodeDataException::get_description() const {
		auto name{get_type_name()};
		if(has_reason()) {
			return
				String{"Failed to convert node to '"} +
				String{name.cbegin(), name.cend()} +
				String{"', because: \n"} +
				reason_->get_full_description();
		}
		return String{"Failed to convert node to '"} + String{name.cbegin(), name.cend()} + String("'");
	}
	
	StringView FailedDecodeDataException::get_type_name() const {
		return type_info_.get_name();
	}
	
	bool FailedDecodeDataException::has_reason() const {
		return reason_.get() != nullptr;
	}
	
	TypeInfo const& FailedDecodeDataException::get_type_info() const {
		return type_info_;
	}
	
	Option<NodeException const&> FailedDecodeDataException::get_reason() const {
		if(reason_.get() != nullptr) {
			return {*reason_};
		}
		return {};
	}
	
	FailedDecodeDataException* FailedDecodeDataException::clone() const {
		return new FailedDecodeDataException{*this};
	}
}