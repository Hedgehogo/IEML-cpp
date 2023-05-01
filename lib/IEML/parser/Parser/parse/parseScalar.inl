//included into ../Parser.hpp
#include "../../helpers/blankLines/blankLines.hpp"

namespace ieml {
	template<typename Char_, typename FileInclude_>
	NodeData Parser<Char_, FileInclude_>::parseScalar(Size indent) {
		if(auto null{parseNull()}) {
			skipBlankLine(pos_, end(), mark_);
			return null.value();
		}
		if(auto classic{parseClassicString(indent)}) {
			skipBlankLine(pos_, end(), mark_);
			return classic.value();
		}
		if(auto notEscaped{parseNotEscapedString(indent)}) {
			return notEscaped.value();
		}
		if(auto raw{parseRaw()}) {
			return raw.value();
		}
		throw FailedParseException{filePath_, FailedParseException::ExpectedScalar, mark_};
	}
}