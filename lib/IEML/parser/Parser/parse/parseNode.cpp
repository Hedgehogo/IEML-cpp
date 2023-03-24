#include "../Parser.hpp"

namespace ieml {
	NodeData Parser::parseNode(Size indent) {
		if(auto file{parseFile(indent)})
			return *file;
		if(auto list{parseList(indent)})
			return *list;
		if(auto map{parseMap(indent)})
			return *map;
		if(auto notScalar{parseNotScalar(indent)})
			return *notScalar;
		return parseScalar(indent);
	}
}