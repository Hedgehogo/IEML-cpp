#include "FailedParseException.hpp"

namespace ieml {
	FailedParseException::FailedParseException(FilePath filePath, Reason reason, Mark mark) :
		WithMarkException(mark), file_path(filePath), reason(reason) {
	}
	
	String getFileDescription(FilePath filePath) {
		if(!filePath.empty())
			return String(" in the file '") + filePath.string() + String("'");
		return "";
	}
	
	String getReasonDescription(FailedParseException::Reason reason) {
		if(reason == FailedParseException::Reason::FailedDetermineType) {
			return "Failed to determine data type.";
		} else if (reason == FailedParseException::Reason::ExpectedMapKey) {
			return "Expected Map Key.";
		} else if (reason == FailedParseException::Reason::ExpectedListItem) {
			return "Expected List Item.";
		} else if (reason == FailedParseException::Reason::ImpermissibleSpace) {
			return "A space was detected. Perhaps you meant to write a tab as an indentation.";
		} else if (reason == FailedParseException::Reason::ImpermissibleTab) {
			return "A tab was detected. A lower level of indentation was expected.";
		} else if (reason == FailedParseException::Reason::AnchorAlreadyExists) {
			return "An attempt was made to take an anchor with the name of an anchor that already exists.";
		}
		return "The end of the file has been reached, but the String is not completed.";
	}
	
	String FailedParseException::getDescription() const {
		return String("Failed to determine the type of data") +
			   getFileDescription(file_path) + String(". ") +
			   getReasonDescription(reason);
	}
	
	FilePath FailedParseException::getFilePath() const {
		return file_path;
	}
	
	FailedParseException::Reason FailedParseException::getReason() const {
		return reason;
	}
}