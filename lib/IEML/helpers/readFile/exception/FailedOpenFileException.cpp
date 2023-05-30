#include "FailedOpenFileException.hpp"

namespace ieml {
	FailedOpenFileException::FailedOpenFileException(FilePath filePath) : filePath(filePath) {
	}
	
	String FailedOpenFileException::getDescription() const {
		return String("Failed to open the file in the '") + filePath.string() + String("' path");
	}
	
	FilePath FailedOpenFileException::getFilePath() {
		return filePath;
	}
}