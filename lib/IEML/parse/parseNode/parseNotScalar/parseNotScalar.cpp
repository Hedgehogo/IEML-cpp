#include "parseNotScalar.hpp"
#include <ctre/functions.hpp>
#include "../../emptyLines/emptyLines.hpp"
#include "../../matchAndMove/matchAndMove.hpp"
#include "../../exceptions/FailedParseException.hpp"

namespace ieml {
	INodeData *parseNotScalar(std::string::const_iterator &pos, std::string::const_iterator end, RefKeeper &refKeeper, Mark &mark, size_t indent) {
		auto currentIndentFind{matchAndMove<tabs>(mark, pos, end)};
		std::size_t currentIndent{static_cast<std::size_t>(currentIndentFind.size())};
		if(currentIndent == indent) {
			bool isList{ctre::starts_with<listSpecial>(pos, end)};
			if(isList) {
				return parseList(pos, end, refKeeper, mark, indent);
			} else {
				return parseMap(pos, end, refKeeper, mark, indent);
			}
		}
		throw FailedParseException{{}, mark};
	}
}