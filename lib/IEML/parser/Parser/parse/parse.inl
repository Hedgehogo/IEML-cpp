//included into ../Parser.hpp
#include <ctre.hpp>
#include "../../helpers/blankLines/blankLines.hpp"

namespace ieml {
	template<typename Char_>
	Size determineIndent(String::const_iterator& pos, String::const_iterator end) {
		return ctre::starts_with<reIndent>(pos, end).end() - pos;
	}
	
	template<typename Char_, typename FileInclude_>
	NodeData Parser<Char_, FileInclude_>::parse() {
		skipBlankLinesLn(pos_, end(), mark_);
		
		Size indent{determineIndent<Char_>(pos_, end())};
		mark_.symbol = indent;
		
		if(filePath_.empty()) {
			return parseNode(indent);
		} else {
			return FileData{parseNode(indent), filePath_};
		}
	}
}