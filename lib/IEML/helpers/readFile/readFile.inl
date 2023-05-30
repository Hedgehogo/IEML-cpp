#include <fstream>
#include "exception/FailedOpenFileException.hpp"

namespace ieml {
	template<typename T>
	std::basic_string<T> readFile(FilePath filePath) {
		std::basic_fstream<T> file{filePath};
		if(!file)
			throw FailedOpenFileException{filePath};
		std::basic_string<T> str;
		std::getline(file, str, static_cast<T>(0));
		return str;
	}
}