#include "parseNode.hpp"
#include <algorithm>
#include "../emptyLines/emptyLines.hpp"
#include "parseScalar/parseScalar.hpp"
#include "parseNotScalar/parseNotScalar.hpp"
#include "parseFile/parseFile.hpp"

namespace ieml {
	NodeData parseNode(std::string::const_iterator& pos, std::string::const_iterator end, const fs::path& filePath, RefKeeper& refKeeper, Mark& mark, size_t indent) {
		if(auto file{parseFile(pos, end, filePath, refKeeper, mark, indent)})
			return *file;
		if(auto list{parseList(pos, end, filePath, refKeeper, mark, indent)})
			return *list;
		if(auto map{parseMap(pos, end, filePath, refKeeper, mark, indent)})
			return *map;
		if(auto notScalar{parseNotScalar(pos, end, filePath, refKeeper, mark, indent)})
			return *notScalar;
		return parseScalar(pos, end, filePath, mark, indent);
	}
}