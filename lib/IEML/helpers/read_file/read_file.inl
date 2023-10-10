#include <fstream>
#include "exception/FailedOpenFileException.hpp"

namespace ieml {
	template<typename T>
	std::basic_string<T> read_file(FilePath file_path) {
		std::basic_fstream<T> file{file_path};
		if(!file)
			throw FailedOpenFileException{file_path};
		std::basic_string<T> str;
		std::getline(file, str, static_cast<T>(0));
		return str;
	}
}