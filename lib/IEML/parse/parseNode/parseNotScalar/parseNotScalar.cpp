#include "parseNotScalar.hpp"
#include <ctre/functions.hpp>
#include "../../emptyLines/emptyLines.hpp"
#include "../../matchAndMove/matchAndMove.hpp"

namespace ieml {
	INodeData *parseNotScalar(Mark& mark, size_t indent, std::string::const_iterator& pos, std::string::const_iterator end) {
		auto currentIndentFind{matchAndMove<tabs>(mark, pos, end)};
		std::size_t currentIndent{static_cast<std::size_t>(currentIndentFind.size())};
		if(currentIndent == indent) {
			bool isList{ctre::starts_with<listSpecial>(pos, end)};
			if(isList) {
				return parseList(mark, indent, pos, end);
			} else {
				return parseMap(mark, indent, pos, end);
			}
		}
	}
}