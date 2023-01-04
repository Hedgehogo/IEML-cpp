#include "FailedParseException.hpp"

namespace ieml {
	FailedParseException::FailedParseException(fs::path filePath, Mark mark) :
		WithMarkException(mark, std::string("Failed to determine the type of data in the file '") + filePath.string() + std::string("'.")){}
}