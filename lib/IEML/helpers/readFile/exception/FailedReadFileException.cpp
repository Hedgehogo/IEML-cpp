#include "FailedReadFileException.hpp"

namespace ieml {
	FailedReadFileException::FailedReadFileException(FilePath filePath) : filePath(filePath) {
	}
	
	String FailedReadFileException::getDescription() const {
		return String("Failed to read the file in the '") + filePath.string() + String("' path");
	}
	
	FilePath FailedReadFileException::getFilePath() {
		return filePath;
	}
}