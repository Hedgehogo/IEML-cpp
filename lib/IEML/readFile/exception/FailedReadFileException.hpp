#pragma once

#include "../../exceptions/BaseException.hpp"
#include "../../fileSystem/fileSystem.hpp"

namespace ieml {
	class FailedReadFileException : public BaseException {
	private:
		FilePath filePath;
	
	public:
		FailedReadFileException(FilePath filePath);
		
		std::string getDescription() const override;
		
		/// @brief Gets the path to the file.
		///
		/// @return Path to the file.
		FilePath getFilePath();
	};
}
