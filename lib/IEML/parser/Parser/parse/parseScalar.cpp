#include "../Parser.hpp"
#include "../../helpers/match/match.hpp"
#include "../../helpers/whitespace/whitespace.hpp"

namespace ieml {
	NodeData Parser::parseScalar(Size indent) {
		if(auto null{parseNull()}) {
			matchAndMove<reWhitespace>(pos_, end(), mark_);
			return null.value();
		}
		if(auto classic{parseClassicString(indent)}) {
			matchAndMove<reWhitespace>(pos_, end(), mark_);
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