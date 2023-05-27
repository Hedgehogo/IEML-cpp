//included into ../Parser.hpp
#include "../../helpers/blankLines/blankLines.hpp"
#include "../../helpers/match/match.hpp"

namespace ieml {
	template<typename Char_>
	Size determineIndent(BasicStringCIter<Char_>& pos, BasicStringCIter<Char_> end, Mark& mark) {
		return matchAndMove<reIndent>(pos, end, mark).end() - pos;
	}
	
	template<typename Char_, typename FileInclude_>
	BasicNodeData<Char_> BasicParser<Char_, FileInclude_>::parse() {
		skipBlankLinesLn<Char_>(pos_, end(), mark_);
		Size indent{determineIndent<Char_>(pos_, end(), mark_)};
		
		BasicNodeData<Char_> data;
		if(filePath_.empty()) {
			data = parseNode(indent);
		} else {
			data = BasicNodeData<Char_>{BasicFileData<Char_>{parseNode(indent), filePath_}};
		}
		
		skipBlankLinesLn(pos_, end(), mark_);
		skipBlankLine(pos_, end(), mark_);
		if(pos_ != end()) {
			except(FailedParseException::Reason::IncompleteDocument);
		}
		return data;
	}
}