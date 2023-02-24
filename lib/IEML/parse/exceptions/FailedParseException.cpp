#include "FailedParseException.hpp"

namespace ieml {
	FailedParseException::FailedParseException(FilePath filePath, Expected expected, Mark mark) :
		WithMarkException(mark), filePath(filePath), expected(expected) {
	}
	
	std::string getFileDescription(FilePath filePath) {
		if(!filePath.empty())
			return std::string(" in the file '") + filePath.string() + std::string("'");
		return "";
	}
	
	std::string getExpectedDescription(FailedParseException::Expected expected) {
		if(expected == FailedParseException::Expected::Scalar) {
			return "Scalar";
		} else if(expected == FailedParseException::Expected::MapKey) {
			return "Map key";
		} else if(expected == FailedParseException::Expected::ListItem) {
			return "List item";
		} else if(expected == FailedParseException::Expected::NotScalar) {
			return "not Scalar";
		}
		return "existing Anchor";
	}
	
	std::string FailedParseException::getDescription() const {
		return std::string("Failed to determine the type of data") +
			   getFileDescription(filePath) + std::string(". Expected ") +
			   getExpectedDescription(expected) + std::string(".");
	}
	
	FilePath FailedParseException::getFilePath() const {
		return filePath;
	}
}