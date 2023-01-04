#include "parseTag.hpp"
#include "../../node/NodeData/tag/TagNodeData.hpp"
#include "../parseNode/parseNode.hpp"
#include "../matchAndMove/matchAndMove.hpp"

namespace ieml {
	INodeData *parseTag(std::string::const_iterator &pos, std::string::const_iterator end, RefKeeper &refKeeper, Mark &mark, size_t indent, bool lineBegin) {
		if(auto tagFind{matchAndMove<tag>(mark, pos + (lineBegin ? indent : 0), pos, end)}; tagFind) {
			int endIndent{*(tagFind.end() - 1) == ' ' ? 2 : 1};
			std::string tagStr{tagFind.begin() + 2, tagFind.end() - endIndent};
			return new TagNodeData{std::unique_ptr<INodeData>(parseRef(pos, end, refKeeper, mark, indent + 1, false)), tagStr};
		} else {
			return parseRef(pos, end, refKeeper, mark, indent + (lineBegin ? 0 : 1), lineBegin);
		}
	}
}