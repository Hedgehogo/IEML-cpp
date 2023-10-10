#include <cstring>
#include "BaseException.hpp"
#include <ostream>

namespace ieml {
	String BaseException::get_full_description() const {
		return get_description();
	}
	
	const char* BaseException::what() const noexcept {
		String str{get_full_description()};
		char* result{new char[str.size() + 1]{}};
		strcpy(result, str.c_str());
		return result;
	}
	
	std::ostream& operator<<(std::ostream& stream, const BaseException& exception) {
		stream << exception.get_full_description();
		return stream;
	}
}