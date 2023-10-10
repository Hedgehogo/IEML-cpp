#include "FailedParseException.hpp"

namespace ieml {
	FailedParseException::FailedParseException(FilePath file_path, Reason reason, Mark mark) :
		WithMarkException(mark), file_path(file_path), reason(reason) {
	}
	
	String get_file_description(FilePath file_path) {
		if(!file_path.empty())
			return String(" in the file '") + file_path.string() + String("'");
		return "";
	}
	
	String get_reason_description(FailedParseException::Reason reason) {
		if(reason == FailedParseException::Reason::FailedDetermineType) {
			return "Failed to determine data type.";
		} else if(reason == FailedParseException::Reason::ExpectedMapKey) {
			return "Expected Map Key.";
		} else if(reason == FailedParseException::Reason::ExpectedListItem) {
			return "Expected List Item.";
		} else if(reason == FailedParseException::Reason::ImpermissibleSpace) {
			return "A space was detected. Perhaps you meant to write a tab as an indentation.";
		} else if(reason == FailedParseException::Reason::ImpermissibleTab) {
			return "A tab was detected. A lower level of indentation was expected.";
		} else if(reason == FailedParseException::Reason::AnchorAlreadyExists) {
			return "An attempt was made to take an anchor with the name of an anchor that already exists.";
		} else if(reason == FailedParseException::Reason::IncompleteString) {
			return "The end of the file has been reached, but the String is not completed.";
		}
		return "There are extra characters at the end of the document.";
	}
	
	String FailedParseException::get_description() const {
		return String("Failed to determine the type of data") +
			   get_file_description(file_path) + String(". ") +
			   get_reason_description(reason);
	}
	
	FilePath FailedParseException::get_file_path() const {
		return file_path;
	}
	
	FailedParseException::Reason FailedParseException::get_reason() const {
		return reason;
	}
}