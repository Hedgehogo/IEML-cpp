//included into ../Parser.hpp
#include "../../helpers/blank_lines/blank_lines.hpp"
#include "../../helpers/match/match.hpp"

namespace ieml {
	static constexpr auto re_list_special = ctll::fixed_string{R"(-( | ?(?=\n)))"};
	
	template<typename Char_, typename FileInclude_>
	Option<BasicListData<Char_>> BasicParser<Char_, FileInclude_>::parse_list(Size indent) {
		if(ctre::starts_with<re_list_special>(pos_, end())) {
			BasicListData<Char_> nodes{};
			PosInfo pos_info{get_pos_info()};
			bool right_indent{true};
			while(right_indent) {
				if(match_and_move<re_list_special, Char_>(pos_info.pos, end(), pos_info.mark)) {
					set_pos_info(pos_info);
					BasicNodeData<Char_> node_data{parse_node(indent + 1)};
					nodes.emplace_back(BasicNode{std::move(node_data), pos_info.mark});
					pos_info = get_pos_info();
					
					if(pos_ != end() && *pos_ != to_char<Char_>('\n'))
						except(FailedParseException::Reason::ExpectedListItem);
					skip_blank_lines_ln<Char_>(pos_info.pos, end(), pos_info.mark);
					right_indent = match_indent<Char_>(pos_info.pos, end(), pos_info.mark, indent);
				} else if(pos_info.pos == end()) {
					break;
				} else if(*pos_info.pos == to_char<Char_>(' ')) {
					except(FailedParseException::Reason::ImpermissibleSpace);
				} else if(*pos_info.pos == to_char<Char_>('\t')) {
					except(FailedParseException::Reason::ImpermissibleTab);
				} else {
					except(FailedParseException::Reason::ExpectedListItem);
				}
			}
			return {nodes};
		}
		return {};
	}
}