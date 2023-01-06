#include "parseRef.hpp"
#include <algorithm>
#include "../emptyLines/emptyLines.hpp"
#include "../match/match.hpp"
#include "../exceptions/FailedParseException.hpp"
#include "../parseNode/parseNode.hpp"

namespace ieml {
	static constexpr auto reTakeRef = ctll::fixed_string{R"(&[^\"\n<> ]* ?)" };
	static constexpr auto reGetRef = ctll::fixed_string{R"(\*[^\"\n<> ]* ?)" };
	
	INodeData *parseRef(std::string::const_iterator &pos, std::string::const_iterator end, const fs::path &filePath, RefKeeper &refKeeper, Mark &mark, size_t indent) {
		if(auto find{matchAndMove<reTakeRef>(mark, pos, end)}; find) {
			int endIndent{*(find.end() - 1) == ' ' ? 1 : 0};
			std::string key{find.begin() + 1, find.end() - endIndent};
			INodeData* nodeData{parseNode(pos, end, filePath, refKeeper, mark, indent)};
			refKeeper.add(key, nodeData);
			return nodeData;
		}
		if(auto find{matchAndMove<reGetRef>(mark, pos, end)}; find) {
			int endIndent{*(find.end() - 1) == ' ' ? 1 : 0};
			std::string key{find.begin() + 1, find.end() - endIndent};
			matchAndMove<reEmptyLine>(mark, pos, end);
			if(auto findData{refKeeper.get(key)}; findData) {
				return findData->copy();
			}
			throw FailedParseException{filePath, mark};
		}
		return parseNode(pos, end, filePath, refKeeper, mark, indent);
	}
}