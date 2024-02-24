//included into ../Parser.hpp

namespace ieml {
	template<typename Char_, typename FileInclude_>
	BasicNodeData<Char_> BasicParser<Char_, FileInclude_>::parse_node(Size indent) {
		if(skip_blank_lines_ln<Char_>(pos_, end(), mark_)) {
			if(!match_indent<Char_>(pos_, end(), mark_, indent)) {
				except(FailedParseException::Reason::FailedDetermineType);
			}
		}
		for(auto& tag: parse_tag(indent)) {
			return BasicNodeData<Char_>{std::move(tag)};
		}
		for(auto& take_anchor: parse_take_anchor(indent)) {
			return BasicNodeData<Char_>{std::move(take_anchor)};
		}
		for(auto& get_anchor: parse_get_anchor(indent)) {
			return BasicNodeData<Char_>{std::move(get_anchor)};
		}
		for(auto& file: parse_file(indent)) {
			return BasicNodeData<Char_>{std::move(file)};
		}
		for(auto& list: parse_list(indent)) {
			return BasicNodeData<Char_>{std::move(list)};
		}
		for(auto& short_list: parse_short_list()) {
			return BasicNodeData<Char_>{std::move(short_list)};
		}
		for(auto& map: parse_map(indent)) {
			return BasicNodeData<Char_>{std::move(map)};
		}
		return parse_scalar(indent);
	}
}