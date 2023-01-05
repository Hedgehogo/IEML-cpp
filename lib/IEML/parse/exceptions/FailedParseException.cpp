#include "FailedParseException.hpp"

namespace ieml {
	FailedParseException::FailedParseException(fs::path filePath, Mark mark) :
		WithMarkException(mark, std::string("Failed to determine the type of data") +
		(filePath.empty() ? std::string("") : std::string(" in the file '") + filePath.string() + std::string("'")) + std::string(".")){}
}