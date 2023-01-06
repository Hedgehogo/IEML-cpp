#include "FailedConvertDataException.hpp"

namespace ieml {
	FailedConvertDataException::FailedConvertDataException(Mark mark, std::string type) :
		WithMarkException(mark, std::string("Failed to convert node to '") + type + std::string("'")) {}
}