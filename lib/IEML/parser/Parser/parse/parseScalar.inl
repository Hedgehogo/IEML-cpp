//included into ../Parser.hpp
#include "../../helpers/blankLines/blankLines.hpp"

namespace ieml {
	template<typename Char_, typename FileInclude_>
	BasicNodeData<Char_> BasicParser<Char_, FileInclude_>::parseScalar(Size indent) {
		if(auto null{parseNull()}) {
			skipBlankLine<Char_>(pos_, end(), mark_);
			return BasicNodeData<Char_>{null.some()};
		}
		if(auto classic{parseClassicString(indent)}) {
			skipBlankLine<Char_>(pos_, end(), mark_);
			return BasicNodeData<Char_>{classic.some()};
		}
		if(auto notEscaped{parseNotEscapedString(indent)}) {
			return BasicNodeData<Char_>{notEscaped.some()};
		}
		if(auto raw{parseRaw()}) {
			return BasicNodeData<Char_>{raw.some()};
		}
		throw FailedParseException{filePath_, FailedParseException::FailedDetermineType, mark_};
	}
}