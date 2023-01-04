#pragma once
#include "../../fileSystem/fileSystem.hpp"
#include "../../exceptions/WithMark/WithMarkException.hpp"

namespace ieml {
	class FailedParseException : public WithMarkException {
	private:
		fs::path filePath;
		
	public:
		FailedParseException(fs::path filePath, Mark mark);
	};
}
