#include "parseScalar.hpp"
#include "../../match/match.hpp"
#include "../../exceptions/FailedParseException.hpp"
#include "parseNull/parseNull.hpp"
#include "parseClassicString/parseClassicString.hpp"
#include "parseUnshieldedString/parseUnshieldedString.hpp"
#include "parseRaw/parseRaw.hpp"

namespace ieml {
	NodeData parseScalar(std::string::const_iterator& pos, std::string::const_iterator end, const FilePath& filePath, Mark& mark, size_t indent) {
		if(auto null{parseNull(pos, end, mark)}) {
			matchAndMove<reWhitespace>(mark, pos, end);
			return null.value();
		}
		if(auto classic{parseClassicString(pos, end, mark)}) {
			matchAndMove<reWhitespace>(mark, pos, end);
			return classic.value();
		}
		if(auto unshielded{parseUnshieldedString(pos, end, mark)}) {
			return unshielded.value();
		}
		if(auto raw{parseRaw(pos, end, mark)}) {
			return raw.value();
		}
		throw FailedParseException{filePath, mark};
	}
}