#include "parseRef.hpp"
#include <algorithm>
#include "../emptyLines/emptyLines.hpp"
#include "../match/match.hpp"
#include "../exceptions/FailedParseException.hpp"
#include "../parseNode/parseNode.hpp"
#include "../parseNode/parseScalar/whitespace.hpp"

namespace ieml {
	static constexpr auto reTakeRef = ctll::fixed_string{R"(&[^\"\n<> ]*)"};
	static constexpr auto reGetRef = ctll::fixed_string{R"(\*[^\"\n<> ]*)"};
	
	Option<NodeData> parseTakeRef(std::string::const_iterator& pos, std::string::const_iterator end, const FilePath& filePath, RefKeeper& refKeeper, Mark& mark, size_t indent) {
		if(auto find{matchAndMove<reTakeRef>(mark, pos, end)}; find) {
			std::string key{find.begin() + 1, find.end()};
			if(pos != end && *pos == ' ')
				++pos;
			NodeData nodeData{parseNode(pos, end, filePath, refKeeper, mark, indent)};
			refKeeper.add(key, nodeData);
			return nodeData;
		}
		return {};
	}
	
	Option<NodeData> parseGetRef(std::string::const_iterator& pos, std::string::const_iterator end, const FilePath& filePath, RefKeeper& refKeeper, Mark& mark, size_t indent) {
		if(auto find{matchAndMove<reGetRef>(mark, pos, end)}; find) {
			std::string key{find.begin() + 1, find.end()};
			matchAndMove<reWhitespace>(mark, pos, end);
			if(auto data{refKeeper.get(key)}) {
				return *data;
			}
			throw FailedParseException{filePath, FailedParseException::Expected::ExistingAnchor, mark};
		}
		return {};
	}
	
	NodeData parseRef(std::string::const_iterator& pos, std::string::const_iterator end, const FilePath& filePath, RefKeeper& refKeeper, Mark& mark, size_t indent) {
		if(auto takeRef{parseTakeRef(pos, end, filePath, refKeeper, mark, indent)}) {
			return takeRef.value();
		}
		if(auto getRef{parseGetRef(pos, end, filePath, refKeeper, mark, indent)}) {
			return getRef.value();
		}
		return parseNode(pos, end, filePath, refKeeper, mark, indent);
	}
}