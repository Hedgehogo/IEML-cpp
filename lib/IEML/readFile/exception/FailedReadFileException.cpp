#include "FailedReadFileException.hpp"

namespace ieml {
	FailedReadFileException::FailedReadFileException(FilePath filePath) : filePath(filePath) {
	}
	
	std::string FailedReadFileException::getDescription() const {
		return std::string("Failed to read the file in the '") + filePath.string() + std::string("' path");
	}
	
	FilePath FailedReadFileException::getFilePath() {
		return filePath;
	}
}