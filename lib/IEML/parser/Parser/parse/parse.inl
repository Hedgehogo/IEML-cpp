//included into ../Parser.hpp
#include "../../helpers/blank_lines/blank_lines.hpp"
#include "../../helpers/match/match.hpp"

namespace ieml {
	template<typename Char_>
	Size determine_indent(BasicStringCIter<Char_>& pos, BasicStringCIter<Char_> end, Mark& mark) {
		return match_and_move<re_indent>(pos, end, mark).end() - pos;
	}
	
	template<typename Char_, typename FileInclude_>
	BasicNodeData<Char_> BasicParser<Char_, FileInclude_>::parse() {
		skip_blank_lines_ln<Char_>(pos_, end(), mark_);
		Size indent{determine_indent<Char_>(pos_, end(), mark_)};
		
		BasicNodeData<Char_> data{BasicNodeData<Char_>{BasicFileData<Char_>{parse_node(indent), file_path_, anchor_keeper_}}};
		
		skip_blank_lines_ln(pos_, end(), mark_);
		skip_blank_line(pos_, end(), mark_);
		if(pos_ != end()) {
			except(FailedParseException::Reason::IncompleteDocument);
		}
		
		return data;
	}
}