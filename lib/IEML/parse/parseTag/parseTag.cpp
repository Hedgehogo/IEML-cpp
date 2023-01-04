#include "parseTag.hpp"
#include "../../node/NodeData/tag/TagNodeData.hpp"
#include "../parseNode/parseNode.hpp"
#include "../matchAndMove/matchAndMove.hpp"

namespace ieml {
	INodeData *parseTag(bool lineBegin, Mark &mark, size_t indent, std::string::const_iterator &pos, std::string::const_iterator end) {
		if(auto tagFind{matchAndMove<tag>(mark, pos + (lineBegin ? indent : 0), pos, end)}; tagFind) {
			int endIndent{*(tagFind.end() - 1) == ' ' ? 2 : 1};
			std::string tagStr{tagFind.begin() + 2, tagFind.end() - endIndent};
			return new TagNodeData{std::unique_ptr<INodeData>(parseNode(false, mark, indent + 1, pos, end)), tagStr};
		} else {
			return parseNode(lineBegin, mark, indent + (lineBegin ? 0 : 1), pos, end);
		}
	}
}