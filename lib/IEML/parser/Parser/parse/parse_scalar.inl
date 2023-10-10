//included into ../Parser.hpp
#include "../../helpers/blank_lines/blank_lines.hpp"

namespace ieml {
	template<typename Char_, typename FileInclude_>
	BasicNodeData<Char_> BasicParser<Char_, FileInclude_>::parse_scalar(Size indent) {
		if(auto null{parse_null()}) {
			skip_blank_line<Char_>(pos_, end(), mark_);
			return BasicNodeData<Char_>{null.some()};
		}
		if(auto classic_string{parse_classic_string(indent)}) {
			skip_blank_line<Char_>(pos_, end(), mark_);
			return BasicNodeData<Char_>{classic_string.some()};
		}
		if(auto line_string{parse_line_string()}) {
			return BasicNodeData<Char_>{line_string.some()};
		}
		if(auto not_escaped_string{parse_not_escaped_string(indent)}) {
			return BasicNodeData<Char_>{not_escaped_string.some()};
		}
		if(auto raw{parse_raw()}) {
			return BasicNodeData<Char_>{raw.some()};
		}
		throw FailedParseException{file_path_, FailedParseException::FailedDetermineType, mark_};
	}
}