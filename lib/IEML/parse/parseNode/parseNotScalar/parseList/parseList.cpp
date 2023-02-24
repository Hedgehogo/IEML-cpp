#include "parseList.hpp"
#include "../../../../node/Node/Node.hpp"
#include "../../../parseTag/parseTag.hpp"
#include "../../../emptyLines/emptyLines.hpp"
#include "../../../match/match.hpp"
#include "../../../exceptions/FailedParseException.hpp"

namespace ieml {
	static constexpr auto reListSpecial = ctll::fixed_string{R"(-[ \n])"};
	
	bool findListSpecial(std::string::const_iterator& pos, std::string::const_iterator end, Mark& mark) {
		bool find{matchAndMove<reListSpecial>(mark, pos, end)};
		if(*(pos - 1) == '\n') {
			--pos;
			--mark.symbol;
		}
		return find;
	}
	
	Option<ListData> parseList(std::string::const_iterator& pos, std::string::const_iterator end, const FilePath& filePath, RefKeeper& refKeeper, Mark& mark, size_t indent) {
		if(ctre::starts_with<reListSpecial>(pos, end)) {
			ListData nodes{};
			Mark currentMark{mark};
			std::size_t currentIndent{indent};
			std::string::const_iterator currentPos{pos};
			while(currentIndent == indent && findListSpecial(currentPos, end, currentMark)) {
				Mark nodeMark{currentMark};
				NodeData nodeData{parseTag(currentPos, end, filePath, refKeeper, currentMark, indent, false)};
				nodes.emplace_back(nodeData, nodeMark);
				
				pos = currentPos;
				mark = currentMark;
				
				if(pos != end && *pos != '\n')
					throw FailedParseException{filePath, mark};
				skipEmptyLines(currentPos, end, currentMark);
				currentIndent = matchAndMove<reTabs>(currentMark, currentPos, end);
			}
			return nodes;
		}
		return {};
	}
}