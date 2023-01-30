#include "parseMap.hpp"
#include "../../../../node/Node/Node.hpp"
#include "../../../parseTag/parseTag.hpp"
#include "../../../emptyLines/emptyLines.hpp"
#include "../../../match/match.hpp"
#include "../../../exceptions/FailedParseException.hpp"
#include "../../../parseRef/parseRef.hpp"
#include "../FindResult/FindResult.hpp"

namespace ieml {
	NodeData parseMap(std::string::const_iterator &pos, std::string::const_iterator end, const fs::path &filePath, RefKeeper &refKeeper, Mark &mark, size_t indent) {
		FindResult currentIndentFind;
		MapNodeData nodes{};
		do {
			if(auto find{matchAndMove<reMapKey>(mark, pos, end)}; find) {
				std::string str;
				Mark nodeMark{mark};
				NodeData nodeData;
				int endIndent{*(find.end() - 1) == ' ' ? 2 : 1};
				if(auto tagFind{ctre::search<reTagSpecial>(find.begin(), find.end())}; tagFind) {
					str = {find.begin(), tagFind.begin()};
					std::string tagStr{tagFind.end(), find.end() - endIndent};
					nodeData = TagNodeData{new NodeData{parseRef(pos, end, filePath, refKeeper, mark, indent + 1)}, tagStr};
				} else {
					str = {find.begin(), find.end() - endIndent};
					nodeData = parseRef(pos, end, filePath, refKeeper, mark, indent + 1);
				}
				nodes.emplace(str, Node{nodeData, nodeMark});
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