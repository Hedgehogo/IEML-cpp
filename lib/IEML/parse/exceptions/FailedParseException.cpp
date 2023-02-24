#include "FailedParseException.hpp"

namespace ieml {
	FailedParseException::FailedParseException(FilePath filePath, Mark mark) :
		WithMarkException(mark), filePath(filePath) {
	}
	
	std::string FailedParseException::getDescription() const {
		return std::string("Failed to determine the type of data") +
			   (filePath.empty() ? std::string("") : std::string(" in the file '") + filePath.string() + std::string("'")) + std::string(".");
	}
	
	FilePath FailedParseException::getFilePath() const {
		return filePath;
	}
}