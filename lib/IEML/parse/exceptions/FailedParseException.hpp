#pragma once

#include "../../fileSystem/fileSystem.hpp"
#include "../../exceptions/WithMark/WithMarkException.hpp"

namespace ieml {
	class FailedParseException : public WithMarkException {
	private:
		FilePath filePath;
	
	public:
		FailedParseException(FilePath filePath, Mark mark);
		
		std::string getDescription() const override;
		
		FilePath getFilePath() const;
	};
}
