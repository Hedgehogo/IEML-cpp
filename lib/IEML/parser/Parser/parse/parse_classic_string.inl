//included into ../Parser.hpp
#include "../../helpers/blank_lines/blank_lines.hpp"

namespace ieml {
	template<typename Char_>
	struct StringMark {
		BasicStringCIter<Char_> pos;
		Size last_length{0};
		Size enter_count{0};
		Size real_length{0};
	};
	
	template<typename Char_>
	bool match_indent(BasicStringCIter<Char_>& pos, BasicStringCIter<Char_> end, Size indent) {
		Size current_indent{0};
		BasicStringCIter<Char_> current_pos{pos};
		while(current_indent < indent && current_pos != end && *current_pos == to_char<Char_>('\t')) {
			current_indent += 1;
			current_pos += 1;
		}
		if(current_indent == indent) {
			pos = current_pos - 1;
			return true;
		}
		return false;
	}
	
	template<typename Char_>
	Option<StringMark<Char_>> is_classic_string(BasicStringCIter<Char_> input_pos, BasicStringCIter<Char_> end, Size indent) {
		if(*input_pos != to_char<Char_>('\"'))
			return {};
		
		StringMark<Char_> mark{input_pos + 1, 1};
		while(true) {
			if(mark.pos == end) {
				return {};
			}
			if(*mark.pos == to_char<Char_>('\"')) {
				break;
			}
			if(*mark.pos == to_char<Char_>('\\')) {
				mark.pos += 1;
				if(mark.pos == end) {
					return {};
				}
				switch(*mark.pos) {
					case to_char<Char_>('\\'):
					case to_char<Char_>('\"'):
					case to_char<Char_>('t'):
					case to_char<Char_>('n'):
						mark.real_length += 1;
						mark.last_length += 2;
						break;
					case to_char<Char_>('\n'):
						mark.enter_count += 1;
						
						mark.pos += 1;
						if(match_indent<Char_>(mark.pos, end, indent)) {
							mark.last_length = indent;
						} else {
							mark.last_length = 0;
							return {};
						}
						break;
					default:
						mark.real_length += 2;
						mark.last_length += 2;
						break;
				}
			} else if(*mark.pos == to_char<Char_>('\n')) {
				mark.enter_count += 1;
				mark.real_length += 1;
				mark.pos += 1;
				if(match_indent<Char_>(mark.pos, end, indent)) {
					mark.last_length = indent;
				} else {
					mark.last_length = 0;
					return {};
				}
			} else {
				mark.last_length += 1;
				mark.real_length += 1;
			}
			mark.pos += 1;
		}
		mark.pos += 1;
		mark.last_length += 1;
		
		return mark;
	}
	
	template<typename Char_>
	void handle_symbol(BasicStringCIter<Char_>& input, BasicStringIter<Char_>& output, Size indent) {
		if(*input == to_char<Char_>('\\')) {
			input += 1;
			if(*input != to_char<Char_>('\n')) {
				switch(*input) {
					case to_char<Char_>('n'):
						*output = to_char<Char_>('\n');
						break;
					case to_char<Char_>('t'):
						*output = to_char<Char_>('\t');
						break;
					case to_char<Char_>('\"'):
						*output = to_char<Char_>('\"');
						break;
					case to_char<Char_>('\\'):
						*output = to_char<Char_>('\\');
						break;
					default:
						*output = to_char<Char_>('\\');
						output += 1;
						*output = *input;
				}
				output += 1;
			}
		} else {
			*output = *input;
			output += 1;
		}
		if(*input == to_char<Char_>('\n')) {
			input += 1 + indent;
		} else {
			input += 1;
		}
	}
	
	template<typename Char_>
	BasicString<Char_> handle_classic_string(BasicStringCIter<Char_> first, Size real_length, Size indent) {
		BasicString<Char_> result(real_length, to_char<Char_>('\0'));
		for(auto pos = result.begin(); pos < result.end();) {
			handle_symbol<Char_>(first, pos, indent);
		}
		return result;
	}
	
	template<typename Char_, typename FileInclude_>
	Option<BasicStringData<Char_>> BasicParser<Char_, FileInclude_>::parse_classic_string(Size indent) {
		for(auto& string_mark: is_classic_string<Char_>(pos_, end(), indent)) {
			BasicString<Char_> result{handle_classic_string<Char_>(pos_ + 1, string_mark.real_length, indent)};
			pos_ = string_mark.pos;
			if(string_mark.enter_count == 0) {
				mark_.symbol += string_mark.last_length;
			} else {
				mark_.symbol = string_mark.last_length;
			}
			mark_.line += string_mark.enter_count;
			return {BasicStringData<Char_>{result}};
		}
		return {};
	}
}