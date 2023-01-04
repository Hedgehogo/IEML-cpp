#include "parseNode.hpp"
#include <algorithm>
#include <ctre/functions.hpp>
#include "../emptyLines/emptyLines.hpp"
#include "../matchAndMove/matchAndMove.hpp"
#include "parseScalar/parseScalar.hpp"
#include "parseNotScalar/parseNotScalar.hpp"
#include "parseFile/parseFile.hpp"

namespace ieml {
	static constexpr auto fileSpecial = ctll::fixed_string{ R"(< )" };
	
	INodeData *parseNode(bool lineBegin, Mark& mark, size_t indent, std::string::const_iterator& pos, std::string::const_iterator end) {
		if(ctre::starts_with<fileSpecial>(pos, end))
			return parseFile(mark, indent, pos, end);
		if(ctre::starts_with<listSpecial>(pos, end))
			return parseList(mark, indent, pos, end);
		if(ctre::starts_with<mapKey>(pos, end))
			return parseMap(mark, indent, pos, end);
		if(matchAndEnter<emptyLine>(mark, pos, end))
			return parseNotScalar(mark, indent, pos, end);
		return parseScalar(mark, indent, pos, end);
	}
}