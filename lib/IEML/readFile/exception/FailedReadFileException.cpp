#include "FailedReadFileException.hpp"

namespace ieml {
	FailedReadFileException::FailedReadFileException(std::string filePath) :
		BaseException(std::string("Failed to read the file in the '") + filePath + std::string("' path")) {}
	
	std::string FailedReadFileException::getFilePath() {
		return filePath;
	}
}