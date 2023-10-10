//included into ../Parser.hpp
#include "../../helpers/match/match.hpp"
#include "../../helpers/blank_lines/blank_lines.hpp"

namespace ieml {
	static constexpr auto re_not_escaped_special = ctll::fixed_string{R"(>>)"};
	static constexpr auto re_line = ctll::fixed_string{R"([^\n]*)"};
	
	template<typename Char_>
	bool match_not_escaped_special(BasicStringCIter<Char_>& pos, BasicStringCIter<Char_> end, Mark& mark) {
		Mark current_mark{mark};
		BasicStringCIter<Char_> current_pos{pos};
		if(!match_and_move<re_not_escaped_special, Char_>(current_pos, end, current_mark))
			return false;
		skip_blank_line<Char_>(current_pos, end, current_mark);
		if(!is_enter<Char_>(current_pos, end))
			return false;
		
		mark = current_mark;
		pos = current_pos;
		return true;
	}
	
	template<typename Char_>
	bool match_enter_and_indent(BasicStringCIter<Char_>& pos, BasicStringCIter<Char_> end, Mark& mark, Size indent) {
		if(is_enter<Char_>(pos, end)) {
			BasicStringCIter<Char_> current_pos{pos + 1};
			Mark current_mark{mark.line + 1, 0};
			if(match_indent<Char_>(current_pos, end, current_mark, indent)) {
				pos = current_pos;
				mark = current_mark;
				return true;
			}
		}
		return false;
	}
	
	template<typename Char_, typename FileInclude_>
	Option<BasicStringData<Char_>> BasicParser<Char_, FileInclude_>::parse_not_escaped_string(Size indent) {
		if(match_not_escaped_special<Char_>(pos_, end(), mark_)) {
			BasicStringData<Char_> result{};
			PosInfo pos_info{get_pos_info()};
			while(match_enter_and_indent<Char_>(pos_info.pos, end(), pos_info.mark, indent)) {
				auto line = match_and_move<re_line, Char_>(pos_info.pos, end(), pos_info.mark);
				if(!result.empty())
					result.push_back(to_char<Char_>('\n'));
				result.append(line.begin(), line.end());
				set_pos_info(pos_info);
			}
			return {result};
		}
		return {};
	}
}