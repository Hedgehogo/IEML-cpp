//included into ../Parser.hpp

namespace ieml {
	template<typename Char_, typename FileInclude_>
	NodeData Parser<Char_, FileInclude_>::parseNode(Size indent) {
		if(auto tag{parseTag(indent)})
			return *tag;
		if(auto anchor{parseAnchor(indent)})
			return *anchor;
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