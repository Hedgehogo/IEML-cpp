#include "parse.hpp"
#include <ctre/functions.hpp>
#include "../reference/RefKeeper/RefKeeper.hpp"
#include "emptyLines/emptyLines.hpp"
#include "parseTag/parseTag.hpp"

namespace ieml {
	std::size_t determineIndent(std::string::const_iterator& pos, std::string::const_iterator end) {
		return ctre::starts_with<tabs>(pos, end).end() - pos;
	}
	
	INodeData *parse(const std::string &config, Mark &mark, RefKeeper &refKeeper, const fs::path &filePath) {
		std::string::const_iterator pos{config.cbegin()};
		std::string::const_iterator end{config.cend()};
		RefKeeper subRefKeeper{refKeeper};
		
		skipEmptyLines(mark, pos, end);
		
		std::size_t indent{determineIndent(pos, end)};
		mark.symbol = indent;
		
		Mark beginMark{mark};
		INodeData* nodeData{parseTag(pos, end, filePath, subRefKeeper, mark, indent, true)};
		mark = beginMark;
		return nodeData;
	}
	
	INodeData *parse(const std::string &config, Mark &mark, const fs::path &filePath) {
		RefKeeper refKeeper{};
		return parse(config, mark, refKeeper, filePath);
	}
}