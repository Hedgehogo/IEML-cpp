#include "FailedOpenFileException.hpp"

namespace ieml {
	FailedOpenFileException::FailedOpenFileException(FilePath file_path) : file_path(file_path) {
	}
	
	String FailedOpenFileException::get_description() const {
		return String("Failed to open the file in the '") + file_path.string() + String("' path");
	}
	
	FilePath FailedOpenFileException::get_file_path() {
		return file_path;
	}
}