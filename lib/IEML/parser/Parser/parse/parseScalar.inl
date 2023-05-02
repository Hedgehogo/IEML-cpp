//included into ../Parser.hpp
#include "../../helpers/blankLines/blankLines.hpp"

namespace ieml {
	template<typename Char_, typename FileInclude_>
	BasicNodeData<Char_> BasicParser<Char_, FileInclude_>::parseScalar(Size indent) {
		if(auto null{parseNull()}) {
			skipBlankLine(pos_, end(), mark_);
			return BasicNodeData<Char_>{null.value()};
		}
		if(auto classic{parseClassicString(indent)}) {
			skipBlankLine(pos_, end(), mark_);
			return BasicNodeData<Char_>{classic.value()};
		}
		if(auto notEscaped{parseNotEscapedString(indent)}) {
			return BasicNodeData<Char_>{notEscaped.value()};
		}
		if(auto raw{parseRaw()}) {
			return BasicNodeData<Char_>{raw.value()};
		}
		throw FailedParseException{filePath_, FailedParseException::ExpectedScalar, mark_};
	}
}