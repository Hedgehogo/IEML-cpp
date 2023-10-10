#pragma once

#include "../../../exception/BaseException.hpp"
#include "../../file_system/file_system.hpp"

namespace ieml {
	class FailedOpenFileException : public BaseException {
	private:
		FilePath file_path;
	
	public:
		FailedOpenFileException(FilePath file_path);
		
		String get_description() const override;
		
		/// @brief Gets the path to the file.
		///
		/// @return Path to the file.
		FilePath get_file_path();
	};
}
