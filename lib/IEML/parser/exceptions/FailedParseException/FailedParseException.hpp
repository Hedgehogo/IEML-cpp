#pragma once

#include "../../../helpers/fileSystem/fileSystem.hpp"
#include "../../../exceptions/WithMark/WithMarkException.hpp"

namespace ieml {
	class FailedParseException : public WithMarkException {
	public:
		enum Reason {
			ExpectedScalar,
			ExpectedNotScalar,
			ExpectedMapKey,
			ExpectedListItem,
			AnchorAlreadyExists,
			IncompleteString,
		};
		
	private:
		FilePath file_path;
		Reason reason;
	
	public:
		FailedParseException(FilePath file_path, Reason reason, Mark mark);
		
		String getDescription() const override;
		
		FilePath getFilePath() const;
	};
}
