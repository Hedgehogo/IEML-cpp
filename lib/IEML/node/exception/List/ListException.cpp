#include "ListException.hpp"

namespace ieml {
	ListException::ListException(Mark mark, Size requested_index, Size list_size) :
		NodeException(mark), requested_index_(requested_index), list_size_(list_size) {
	}
	
	String ListException::get_description() const {
		return String{"It is not possible to get an item outside the list boundary. Item index: "} +
			std::to_string(requested_index_) + String{". List size: "} + std::to_string(list_size_) + String{"."};
	}
	
	Size ListException::get_requested_index() const {
		return requested_index_;
	}
	
	Size ListException::get_list_size() const {
		return list_size_;
	}
	
	ListException* ListException::clone() const {
		return new ListException{*this};
	}
}