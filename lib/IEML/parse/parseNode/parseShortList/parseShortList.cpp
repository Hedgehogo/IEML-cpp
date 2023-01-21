#include "parseShortList.hpp"
#include "../../find/find.hpp"
#include "../../match/match.hpp"

namespace ieml {
	static constexpr auto special = ctll::fixed_string{ R"([\[\]\"]|, ?)" };
	
	INodeData *parseSubShortList(std::string::const_iterator &pos, std::string::const_iterator end, const fs::path &filePath, RefKeeper &refKeeper, Mark &mark, size_t indent) {
		auto listEnd = ieml::rfind(pos, end, ']');
		//Planned
	}
	
	INodeData *parseShortList(std::string::const_iterator &pos, std::string::const_iterator end, const fs::path &filePath, RefKeeper &refKeeper, Mark &mark, size_t indent) {
		auto lineEnd = ieml::find(pos, end, '\n');
		INodeData* nodeData{parseSubShortList(pos, lineEnd, filePath, refKeeper, mark, indent)};
		pos = lineEnd;
		return nodeData;
	}
}