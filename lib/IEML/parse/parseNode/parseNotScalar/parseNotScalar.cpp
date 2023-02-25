#include "parseNotScalar.hpp"
#include <ctre/functions.hpp>
#include "../../emptyLines/emptyLines.hpp"
#include "../../match/match.hpp"
#include "../../exceptions/FailedParseException.hpp"

namespace ieml {
	Option<NodeData> parseNotScalar(std::string::const_iterator& pos, std::string::const_iterator end, const FilePath& filePath, RefKeeper& refKeeper, Mark& mark, size_t indent) {
		if(matchAndEnter<reBlankLine>(mark, pos, end)) {
			skipBlankLines(pos, end, mark);
			std::size_t currentIndent{matchAndMove<reTabs>(mark, pos, end)};
			if(currentIndent == indent) {
				if(auto list{parseList(pos, end, filePath, refKeeper, mark, indent)}) {
					return list.value();
				}
				if(auto map{parseMap(pos, end, filePath, refKeeper, mark, indent)}) {
					return map.value();
				}
			}
			throw FailedParseException{filePath, FailedParseException::Expected::NotScalar, mark};
		}
		return {};
	}
}