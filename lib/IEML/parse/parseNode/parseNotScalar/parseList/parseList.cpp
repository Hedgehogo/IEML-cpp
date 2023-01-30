#include "parseList.hpp"
#include "../../../../node/Node/Node.hpp"
#include "../../../parseTag/parseTag.hpp"
#include "../../../emptyLines/emptyLines.hpp"
#include "../../../match/match.hpp"
#include "../../../exceptions/FailedParseException.hpp"
#include "../FindResult/FindResult.hpp"

namespace ieml {
	NodeData parseList(std::string::const_iterator &pos, std::string::const_iterator end, const fs::path &filePath, RefKeeper &refKeeper, Mark &mark, size_t indent) {
		FindResult currentIndentFind;
		ListNodeData nodes{};
		do {
			if(auto find{matchAndMove<reListSpecial>(mark, pos, end)}; find) {
				Mark nodeMark{mark};
				NodeData nodeData{parseTag(pos, end, filePath, refKeeper, mark, indent, false)};
				nodes.emplace_back(nodeData, nodeMark);
				
				currentIndentFind = matchAndMove<reTabs>(mark, pos, end);
			} else {
				break;
			}
		} while(currentIndentFind.size() == indent);
		pos = currentIndentFind.begin();
		mark.symbol = 0;
		return nodes;
	}
}