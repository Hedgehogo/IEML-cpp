#include "parseNode.hpp"
#include <algorithm>
#include "../emptyLines/emptyLines.hpp"
#include "../match/match.hpp"
#include "../exceptions/FailedParseException.hpp"
#include "parseScalar/parseScalar.hpp"
#include "parseNotScalar/parseNotScalar.hpp"
#include "parseFile/parseFile.hpp"

namespace ieml {
	static constexpr auto fileSpecial = ctll::fixed_string{ R"(< )" };
	
	NodeData parseNode(std::string::const_iterator &pos, std::string::const_iterator end, const fs::path &filePath, RefKeeper &refKeeper, Mark &mark, size_t indent) {
		if(ctre::starts_with<fileSpecial>(pos, end))
			return parseFile(pos, end, filePath, refKeeper, mark, indent);
		if(ctre::starts_with<reListSpecial>(pos, end))
			return parseList(pos, end, filePath, refKeeper, mark, indent);
		if(ctre::starts_with<reMapKey>(pos, end))
			return parseMap(pos, end, filePath, refKeeper, mark, indent);
		if(matchAndEnter<reEmptyLine>(mark, pos, end))
			return parseNotScalar(pos, end, filePath, refKeeper, mark, indent);
		return parseScalar(pos, end, filePath, mark, indent);
	}
}