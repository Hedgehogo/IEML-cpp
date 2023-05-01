#include "../Parser.hpp"
#include <ctre.hpp>
#include "../../helpers/blankLines/blankLines.hpp"

namespace ieml {
	Size determineIndent(String::const_iterator& pos, String::const_iterator end) {
		return ctre::starts_with<reIndent>(pos, end).end() - pos;
	}
	
	NodeData Parser::parse() {
		skipBlankLinesLn(pos_, end(), mark_);
		
		Size indent{determineIndent(pos_, end())};
		mark_.symbol = indent;
		
		if(filePath_.empty()) {
			return parseNode(indent);
		} else {
			return FileData{parseNode(indent), filePath_};
		}
	}
}