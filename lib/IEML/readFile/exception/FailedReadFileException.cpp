#include "FailedReadFileException.hpp"

namespace ieml {
	FailedReadFileException::FailedReadFileException(fs::path filePath) :
		BaseException(std::string("Failed to read the file in the '") + filePath.string() + std::string("' path")) {}
	
	fs::path FailedReadFileException::getFilePath() {
		return filePath;
	}
}