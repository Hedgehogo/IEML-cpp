//included into ../Parser.hpp
#include "../../helpers/blankLines/blankLines.hpp"

namespace ieml {
	template<typename Char_>
	Size determineIndent(BasicStringCIter<Char_>& pos, BasicStringCIter<Char_> end) {
		return ctre::starts_with<reIndent>(pos, end).end() - pos;
	}
	
	template<typename Char_, typename FileInclude_>
	BasicNodeData<Char_> BasicParser<Char_, FileInclude_>::parse() {
		skipBlankLinesLn<Char_>(pos_, end(), mark_);
		
		Size indent{determineIndent<Char_>(pos_, end())};
		mark_.symbol = indent;
		
		if(filePath_.empty()) {
			return parseNode(indent);
		} else {
			return BasicNodeData<Char_>{BasicFileData<Char_>{parseNode(indent), filePath_}};
		}
	}
}