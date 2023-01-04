#pragma once
#include "../../exceptions/BaseException.hpp"

namespace ieml {
	class FailedReadFileException : public BaseException {
	private:
		std::string filePath;
	
	public:
		FailedReadFileException(std::string filePath);
		
		/// @brief Gets the path to the file.
		///
		/// @return Path to the file.
		std::string getFilePath();
	};
}
