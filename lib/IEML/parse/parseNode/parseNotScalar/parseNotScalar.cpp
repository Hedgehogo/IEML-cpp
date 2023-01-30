#include "parseNotScalar.hpp"
#include <ctre/functions.hpp>
#include "../../emptyLines/emptyLines.hpp"
#include "../../match/match.hpp"
#include "../../exceptions/FailedParseException.hpp"

namespace ieml {
	NodeData parseNotScalar(std::string::const_iterator &pos, std::string::const_iterator end, const fs::path &filePath, RefKeeper &refKeeper, Mark &mark, size_t indent) {
		auto currentIndentFind{matchAndMove<reTabs>(mark, pos, end)};
		std::size_t currentIndent{static_cast<std::size_t>(currentIndentFind.size())};
		if(currentIndent == indent) {
			bool isList{ctre::starts_with<reListSpecial>(pos, end)};
			if(isList) {
				return parseList(pos, end, filePath, refKeeper, mark, indent);
			} else {
				return parseMap(pos, end, filePath, refKeeper, mark, indent);
			}
		}
		throw FailedParseException{filePath, mark};
	}
}