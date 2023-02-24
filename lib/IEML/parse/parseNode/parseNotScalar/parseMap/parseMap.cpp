#include "parseMap.hpp"
#include "../../../../node/Node/Node.hpp"
#include "../../../parseTag/parseTag.hpp"
#include "../../../emptyLines/emptyLines.hpp"
#include "../../../match/match.hpp"
#include "../../../parseRef/parseRef.hpp"
#include "../../../exceptions/FailedParseException.hpp"

namespace ieml {
	static constexpr auto reMapKey = ctll::fixed_string{R"([^\"\n<>]*?: ?)"};
	
	Option<MapData> parseMap(std::string::const_iterator& pos, std::string::const_iterator end, const FilePath& filePath, RefKeeper& refKeeper, Mark& mark, size_t indent) {
		if(ctre::starts_with<reMapKey>(pos, end)) {
			MapData nodes{};
			Mark currentMark{mark};
			std::size_t currentIndent{indent};
			std::string::const_iterator currentPos{pos};
			while(currentIndent == indent) {
				if(auto find{matchAndMove<reMapKey>(currentMark, currentPos, end)}) {
					std::string::const_iterator findEnd{find.end() - (*(find.end() - 1) == ' ' ? 2 : 1)};
					std::string str;
					Mark nodeMark{currentMark};
					NodeData nodeData;
					if(auto tagFind{ctre::search<reTagSpecial>(find.begin(), find.end())}) {
						str = {find.begin(), tagFind.begin()};
						std::string tagStr{tagFind.end(), findEnd};
						nodeData = TagData{new NodeData{parseRef(currentPos, end, filePath, refKeeper, currentMark, indent + 1)}, tagStr};
					} else {
						str = {find.begin(), findEnd};
						nodeData = parseRef(currentPos, end, filePath, refKeeper, currentMark, indent + 1);
					}
					nodes.emplace(str, Node{nodeData, nodeMark});
					
					pos = currentPos;
					mark = currentMark;
					
					if(pos != end && *pos != '\n')
						throw FailedParseException{filePath, FailedParseException::Expected::MapKey, mark};
					skipEmptyLines(currentPos, end, currentMark);
					currentIndent = matchAndMove<reTabs>(currentMark, currentPos, end).size();
				} else if(currentPos == end) {
					break;
				} else {
					throw FailedParseException{filePath, FailedParseException::Expected::MapKey, mark};
				}
			}
			if(currentIndent > indent)
				throw FailedParseException{filePath, FailedParseException::Expected::MapKey, mark};
			return nodes;
		}
		return {};
	}
}