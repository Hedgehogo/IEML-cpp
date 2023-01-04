#pragma once
#include "../../exceptions/BaseException.hpp"
#include "../../fileSystem/fileSystem.hpp"

namespace ieml {
	class FailedReadFileException : public BaseException {
	private:
		fs::path filePath;
	
	public:
		FailedReadFileException(fs::path filePath);
		
		/// @brief Gets the path to the file.
		///
		/// @return Path to the file.
		fs::path getFilePath();
	};
}
