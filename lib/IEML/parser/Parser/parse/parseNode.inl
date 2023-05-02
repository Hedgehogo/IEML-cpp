//included into ../Parser.hpp

namespace ieml {
	template<typename Char_, typename FileInclude_>
	BasicNodeData<Char_> BasicParser<Char_, FileInclude_>::parseNode(Size indent) {
		if(auto tag{parseTag(indent)})
			return BasicNodeData<Char_>{*tag};
		if(auto anchor{parseAnchor(indent)})
			return *anchor;
		if(auto file{parseFile(indent)})
			return BasicNodeData<Char_>{*file};
		if(auto list{parseList(indent)})
			return BasicNodeData<Char_>{*list};
		if(auto map{parseMap(indent)})
			return BasicNodeData<Char_>{*map};
		if(auto notScalar{parseNotScalar(indent)})
			return *notScalar;
		return parseScalar(indent);
	}
}