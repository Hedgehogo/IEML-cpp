#include "parseNode.hpp"
#include <algorithm>
#include <ctre/functions.hpp>
#include "../emptyLines/emptyLines.hpp"
#include "../matchAndMove/matchAndMove.hpp"
#include "../exceptions/FailedParseException.hpp"
#include "parseScalar/parseScalar.hpp"
#include "parseNotScalar/parseNotScalar.hpp"
#include "parseFile/parseFile.hpp"

namespace ieml {
	static constexpr auto fileSpecial = ctll::fixed_string{ R"(< )" };
	
	INodeData *parseNode(std::string::const_iterator &pos, std::string::const_iterator end, RefKeeper &refKeeper, Mark &mark, size_t indent, bool lineBegin) {
		if(ctre::starts_with<fileSpecial>(pos, end))
			return parseFile(pos, end, refKeeper, mark, indent);
		if(ctre::starts_with<listSpecial>(pos, end))
			return parseList(pos, end, refKeeper, mark, indent);
		if(ctre::starts_with<mapKey>(pos, end))
			return parseMap(pos, end, refKeeper, mark, indent);
		if(matchAndEnter<emptyLine>(mark, pos, end))
			return parseNotScalar(pos, end, refKeeper, mark, indent);
		return parseScalar(pos, end, mark, indent);
	}
	
	static constexpr auto takeRef = ctll::fixed_string{ R"(&[^\"\n> ]* ?)" };
	static constexpr auto getRef = ctll::fixed_string{ R"(\*[^\"\n> ]* ?)" };
	
	INodeData *parseRef(std::string::const_iterator &pos, std::string::const_iterator end, RefKeeper &refKeeper, Mark &mark, size_t indent, bool lineBegin) {
		if(auto find{matchAndMove<takeRef>(mark, pos, end)}; find) {
			int endIndent{*(find.end() - 1) == ' ' ? 1 : 0};
			std::string key{find.begin() + 1, find.end() - endIndent};
			INodeData* nodeData{parseNode(pos, end, refKeeper, mark, indent, lineBegin)};
			refKeeper.add(key, nodeData);
			return nodeData;
		}
		if(auto find{matchAndMove<getRef>(mark, pos, end)}; find) {
			int endIndent{*(find.end() - 1) == ' ' ? 1 : 0};
			std::string key{find.begin() + 1, find.end() - endIndent};
			matchAndMove<emptyLine>(mark, pos, end);
			if(auto findData{refKeeper.find(key)}; findData != refKeeper.end()) {
				return findData->second->copy();
			}
			throw FailedParseException{{}, mark};
		}
		return parseNode(pos, end, refKeeper, mark, indent, lineBegin);
	}
}