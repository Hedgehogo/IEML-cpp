#include "parseList.hpp"
#include "../../../../node/NodeData/tag/TagNodeData.hpp"
#include "../../../../node/NodeData/list/ListNodeData.hpp"
#include "../../../parseTag/parseTag.hpp"
#include "../../../emptyLines/emptyLines.hpp"
#include "../../../matchAndMove/matchAndMove.hpp"
#include "../FindResult/FindResult.hpp"

namespace ieml {
	INodeData *parseList(Mark &mark, size_t indent, std::string::const_iterator& pos, std::string::const_iterator end) {
		FindResult currentIndentFind;
		std::vector<Node> nodes{};
		do {
			if(auto find{matchAndMove<listSpecial>(mark, pos, end)}; find) {
				Mark nodeMark{mark};
				INodeData* nodeData{parseTag(false, mark, indent, pos, end)};
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