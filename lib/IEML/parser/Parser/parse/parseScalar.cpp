#include "../Parser.hpp"
#include "../../helpers/blankLines/blankLines.hpp"

namespace ieml {
	NodeData Parser::parseScalar(Size indent) {
		if(auto null{parseNull()}) {
			skipBlankLine(pos_, end(), mark_);
			return null.value();
		}
		if(auto classic{parseClassicString(indent)}) {
			skipBlankLine(pos_, end(), mark_);
			return classic.value();
		}
		if(auto unshielded{parseNotEscapedString(indent)}) {
			return unshielded.value();
		}
		if(auto raw{parseRaw()}) {
			return raw.value();
		}
		throw FailedParseException{filePath_, FailedParseException::ExpectedScalar, mark_};
	}
}