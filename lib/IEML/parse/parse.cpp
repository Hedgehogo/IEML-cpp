#include "parse.hpp"
#include <algorithm>
#include <ctre/functions.hpp>
#include "../node/NodeData/tag/TagNodeData.hpp"
#include "emptyLines/emptyLines.hpp"
#include "parseNode/parseNode.hpp"
#include "parseTag/parseTag.hpp"

namespace ieml {
	std::size_t determineIndent(std::string::const_iterator& pos, std::string::const_iterator end) {
		return ctre::starts_with<tabs>(pos, end).end() - pos;
	}
	
	INodeData *parse(const std::string &config, Mark &mark) {
		std::string::const_iterator pos{config.cbegin()};
		std::string::const_iterator end{config.cend()};
		
		skipEmptyLines(mark, pos, end);
		
		std::size_t indent{determineIndent(pos, end)};
		mark.symbol = indent;
		
		Mark beginMark{mark};
		INodeData* nodeData{parseTag(true, mark, indent, pos, end)};
		mark = beginMark;
		return nodeData;
	}
}