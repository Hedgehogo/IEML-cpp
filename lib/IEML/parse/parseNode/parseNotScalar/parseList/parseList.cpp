#include "parseList.hpp"
#include "../../../../node/NodeData/list/ListNodeData.hpp"
#include "../../../parseTag/parseTag.hpp"
#include "../../../emptyLines/emptyLines.hpp"
#include "../../../match/match.hpp"
#include "../../../exceptions/FailedParseException.hpp"
#include "../FindResult/FindResult.hpp"

namespace ieml {
	INodeData *parseList(std::string::const_iterator &pos, std::string::const_iterator end, const fs::path &filePath, RefKeeper &refKeeper, Mark &mark, size_t indent) {
		FindResult currentIndentFind;
		std::vector<Node> nodes{};
		do {
			if(auto find{matchAndMove<listSpecial>(mark, pos, end)}; find) {
				Mark nodeMark{mark};
				INodeData* nodeData{parseTag(pos, end, filePath, refKeeper, mark, indent, false)};
				nodes.emplace_back(std::unique_ptr<INodeData>{nodeData}, nodeMark);
				
				currentIndentFind = matchAndMove<tabs>(mark, pos, end);
			} else {
				break;
			}
		} while(currentIndentFind.size() == indent);
		pos = currentIndentFind.begin();
		mark.symbol = 0;
		return new ListNodeData{std::move(nodes)};
	}
}