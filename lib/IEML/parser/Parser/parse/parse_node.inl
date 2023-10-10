//included into ../Parser.hpp

namespace ieml {
	template<typename Char_, typename FileInclude_>
	BasicNodeData<Char_> BasicParser<Char_, FileInclude_>::parse_node(Size indent) {
		if(skip_blank_lines_ln<Char_>(pos_, end(), mark_)) {
			if(!match_indent<Char_>(pos_, end(), mark_, indent)) {
				except(FailedParseException::Reason::FailedDetermineType);
			}
		}
		if(auto tag{parse_tag(indent)})
			return BasicNodeData<Char_>{tag.some()};
		if(auto take_anchor{parse_take_anchor(indent)})
			return BasicNodeData<Char_>{take_anchor.some()};
		if(auto get_anchor{parse_get_anchor(indent)})
			return BasicNodeData<Char_>{get_anchor.some()};
		if(auto file{parse_file(indent)})
			return BasicNodeData<Char_>{file.some()};
		if(auto list{parse_list(indent)})
			return BasicNodeData<Char_>{list.some()};
		if(auto short_list{parse_short_list()})
			return BasicNodeData<Char_>{short_list.some()};
		if(auto map{parse_map(indent)})
			return BasicNodeData<Char_>{map.some()};
		return parse_scalar(indent);
	}
}