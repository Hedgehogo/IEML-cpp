#include "parseTag.hpp"
#include "../parseRef/parseRef.hpp"
#include "../match/match.hpp"

namespace ieml {
	NodeData parseTag(std::string::const_iterator& pos, std::string::const_iterator end, const FilePath& filePath, RefKeeper& refKeeper, Mark& mark, size_t indent, bool lineBegin) {
		if(auto tagFind{matchAndMove<reTag>(pos + (lineBegin ? indent : 0), pos, end, mark)}; tagFind) {
			int endIndent{*(tagFind.end() - 1) == ' ' ? 2 : 1};
			std::string tagStr{tagFind.begin() + 2, tagFind.end() - endIndent};
			return TagData{NodeData{parseRef(pos, end, filePath, refKeeper, mark, indent + 1)}, tagStr};
		} else {
			return parseRef(pos, end, filePath, refKeeper, mark, indent + (lineBegin ? 0 : 1));
		}
	}
}