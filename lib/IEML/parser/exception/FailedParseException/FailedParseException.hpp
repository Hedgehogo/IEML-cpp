#pragma once

#include "../../../helpers/fileSystem/fileSystem.hpp"
#include "../../../node/exception/WithMark/WithMarkException.hpp"

namespace ieml {
	class FailedParseException : public WithMarkException {
	public:
		enum Reason {
			FailedDetermineType,
			ExpectedMapKey,
			ExpectedListItem,
			ImpermissibleSpace,
			ImpermissibleTab,
			AnchorAlreadyExists,
			IncompleteString,
		};
	
	private:
		FilePath file_path;
		Reason reason;
	
	public:
		FailedParseException(FilePath filePath, Reason reason, Mark mark);
		
		String getDescription() const override;
		
		FilePath getFilePath() const;
		
		Reason getReason() const;
	};
}
