#include "parse.hpp"
#include <ctre/functions.hpp>
#include "emptyLines/emptyLines.hpp"
#include "parseTag/parseTag.hpp"

namespace ieml {
	std::size_t determineIndent(std::string::const_iterator& pos, std::string::const_iterator end) {
		return ctre::starts_with<reTabs>(pos, end).end() - pos;
	}
	
	NodeData parse(const std::string& config, Mark& mark, RefKeeper& refKeeper, const FilePath& filePath) {
		std::string::const_iterator pos{config.cbegin()};
		std::string::const_iterator end{config.cend()};
		
		skipBlankLines(pos, end, mark);
		
		std::size_t indent{determineIndent(pos, end)};
		mark.symbol = indent;
		
		Mark beginMark{mark};
		NodeData nodeData{parseTag(pos, end, filePath, refKeeper, mark, indent, true)};
		mark = beginMark;
		return nodeData;
	}
	
	NodeData parse(const std::string& config, Mark& mark, const FilePath& filePath) {
		RefKeeper refKeeper{};
		return parse(config, mark, refKeeper, filePath);
	}
}