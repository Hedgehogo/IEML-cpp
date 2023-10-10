//included into blank_lines.hpp
#include "../to_char/to_char.hpp"

namespace ieml {
	template<typename Char_>
	bool is_enter(BasicStringCIter<Char_> pos, BasicStringCIter<Char_> end) {
		return pos != end && *pos == to_char<Char_>('\n');
	}
	
	template<typename Char_>
	bool match_enter(BasicStringCIter<Char_>& pos, BasicStringCIter<Char_> end, Mark& mark) {
		if(is_enter<Char_>(pos, end)) {
			mark.enter<Char>(pos);
			return true;
		}
		return false;
	}
	
	template<typename Char_>
	bool match_indent(BasicStringCIter<Char_>& pos, BasicStringCIter<Char_> end, Mark& mark, Size indent) {
		Size current_indent{0};
		BasicStringCIter<Char_> current_pos{pos};
		while(current_indent < indent && current_pos != end && *current_pos == to_char<Char_>('\t')) {
			current_indent += 1;
			current_pos += 1;
		}
		if(current_indent == indent) {
			pos = current_pos;
			mark.symbol += indent;
			return true;
		}
		return false;
	}
	
	template<typename Char_>
	bool skip_blank_line(BasicStringCIter<Char_>& pos, BasicStringCIter<Char_> end, Mark& mark) {
		if(auto line{ctre::starts_with<re_blank_line>(pos, end)}; line.end() != pos) {
			mark.symbol += line.size();
			pos = line.end();
			return true;
		}
		return false;
	}
	
	template<typename Char_>
	bool skip_blank_lines_ln(BasicStringCIter<Char_>& pos, BasicStringCIter<Char_> end, Mark& mark) {
		auto line{ctre::starts_with<re_blank_line>(pos, end)};
		if(line && is_enter<Char_>(line.end(), end)) {
			do {
				pos = line.end() + 1;
				mark.enter();
				line = ctre::starts_with<re_blank_line>(line.end() + 1, end);
			} while(line && is_enter<Char_>(line.end(), end));
			return true;
		}
		return false;
	}
}