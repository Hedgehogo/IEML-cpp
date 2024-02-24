//included into ../Parser.hpp
#include "../../helpers/blank_lines/blank_lines.hpp"

namespace ieml {
	template<typename Char_, typename FileInclude_>
	BasicNodeData<Char_> BasicParser<Char_, FileInclude_>::parse_scalar(Size indent) {
		for(auto& null: parse_null()) {
			skip_blank_line<Char_>(pos_, end(), mark_);
			return BasicNodeData<Char_>{std::move(null)};
		}
		for(auto& classic_string: parse_classic_string(indent)) {
			skip_blank_line<Char_>(pos_, end(), mark_);
			return BasicNodeData<Char_>{std::move(classic_string)};
		}
		for(auto& line_string: parse_line_string()) {
			return BasicNodeData<Char_>{std::move(line_string)};
		}
		for(auto& not_escaped_string: parse_not_escaped_string(indent)) {
			return BasicNodeData<Char_>{std::move(not_escaped_string)};
		}
		for(auto& raw: parse_raw()) {
			return BasicNodeData<Char_>{std::move(raw)};
		}
		throw FailedParseException{file_path_, FailedParseException::FailedDetermineType, mark_};
	}
}