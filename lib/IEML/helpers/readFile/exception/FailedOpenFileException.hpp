#pragma once

#include "../../../exception/BaseException.hpp"
#include "../../fileSystem/fileSystem.hpp"

namespace ieml {
	class FailedOpenFileException : public BaseException {
	private:
		FilePath filePath;
	
	public:
		FailedOpenFileException(FilePath filePath);
		
		String getDescription() const override;
		
		/// @brief Gets the path to the file.
		///
		/// @return Path to the file.
		FilePath getFilePath();
	};
}
