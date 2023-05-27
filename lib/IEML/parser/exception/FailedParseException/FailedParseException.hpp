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
			IncompleteDocument,
		};
	
	private:
		FilePath file_path;
		Reason reason;
	
	public:
		FailedParseException(FilePath filePath, Reason reason, Mark mark);
		
		String get_description() const override;
		
		FilePath get_file_path() const;
		
		Reason get_reason() const;
	};
}
