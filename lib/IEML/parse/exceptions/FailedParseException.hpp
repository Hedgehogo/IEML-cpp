#pragma once

#include "../../fileSystem/fileSystem.hpp"
#include "../../exceptions/WithMark/WithMarkException.hpp"

namespace ieml {
	class FailedParseException : public WithMarkException {
	public:
		enum Expected {
			Scalar,
			MapKey,
			ListItem,
			NotScalar,
			ExistingAnchor
		};
		
	private:
		FilePath filePath;
		Expected expected;
	
	public:
		FailedParseException(FilePath filePath, Expected expected, Mark mark);
		
		std::string getDescription() const override;
		
		FilePath getFilePath() const;
	};
}
