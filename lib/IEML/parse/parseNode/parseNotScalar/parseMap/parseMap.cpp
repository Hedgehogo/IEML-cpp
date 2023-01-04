#include "parseMap.hpp"
#include "../../../../node/NodeData/tag/TagNodeData.hpp"
#include "../../../../node/NodeData/map/MapNodeData.hpp"
#include "../../../parseTag/parseTag.hpp"
#include "../../../emptyLines/emptyLines.hpp"
#include "../../../matchAndMove/matchAndMove.hpp"
#include "../../parseNode.hpp"
#include "../FindResult/FindResult.hpp"

namespace ieml {
	INodeData *parseMap(Mark &mark, size_t indent, std::string::const_iterator& pos, std::string::const_iterator end) {
		FindResult currentIndentFind;
		std::map<std::string, Node> nodes{};
		do {
			if(auto find{matchAndMove<mapKey>(mark, pos, end)}; find) {
				std::string str;
				Mark nodeMark{mark};
				INodeData* nodeData{nullptr};
				int endIndent{*(find.end() - 1) == ' ' ? 2 : 1};
				if(auto tagFind{ctre::search<tagSpecial>(find.begin(), find.end())}; tagFind) {
					str = {find.begin(), tagFind.begin()};
					std::string tagStr{tagFind.end(), find.end() - endIndent};
					nodeData = new TagNodeData{std::unique_ptr<INodeData>(parseNode(false, mark, indent + 1, pos, end)), tagStr};
				} else {
					str = {find.begin(), find.end() - endIndent};
					nodeData = parseNode(false, mark, indent + 1, pos, end);
				}
				nodes.emplace(str, Node{std::unique_ptr<INodeData>{nodeData}, nodeMark});
				currentIndentFind = matchAndMove<tabs>(mark, pos, end);
			} else {
				break;
			}
		} while(currentIndentFind.size() == indent);
		pos = currentIndentFind.begin();
		mark.symbol = 0;
		return new MapNodeData{std::move(nodes)};
	}
}