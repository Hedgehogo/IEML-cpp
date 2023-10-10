//included into ../Parser.hpp
#include "../../helpers/blank_lines/blank_lines.hpp"
#include "../../helpers/match/match.hpp"
#include "../../helpers/tag/tag.hpp"

namespace ieml {
	static constexpr auto re_map_key = ctll::fixed_string{R"(([^\n]*?):( | ?(?=\n)))"};
	
	template<typename Char_, typename FileInclude_>
	Option<BasicMapData<Char_>> BasicParser<Char_, FileInclude_>::parse_map(Size indent) {
		if(ctre::starts_with<re_map_key>(pos_, end())) {
			BasicMapData<Char_> nodes{};
			PosInfo pos_info{get_pos_info()};
			bool right_indent{true};
			while(right_indent) {
				if(pos_info.pos == end()) {
					break;
				} else if(*pos_info.pos == to_char<Char_>(' ')) {
					BasicString<Char_> str{pos_info.pos, end()};
					except(FailedParseException::Reason::ImpermissibleSpace);
				} else if(*pos_info.pos == to_char<Char_>('\t')) {
					except(FailedParseException::Reason::ImpermissibleTab);
				} else if(auto find{match_and_move<re_map_key, Char_>(pos_info.pos, end(), pos_info.mark)}) {
					set_pos_info(pos_info);
					BasicString<Char_> key_str{find.template get<1>().str()};
					BasicNodeData node_data{parse_node(indent + 1)};
					nodes.emplace(key_str, BasicNode<Char_>{node_data, pos_info.mark});
					pos_info = get_pos_info();
					
					if(pos_ != end() && *pos_ != to_char<Char_>('\n'))
						except(FailedParseException::Reason::ExpectedMapKey);
					skip_blank_lines_ln<Char_>(pos_info.pos, end(), pos_info.mark);
					right_indent = match_indent<Char_>(pos_info.pos, end(), pos_info.mark, indent);
				} else {
					except(FailedParseException::Reason::ExpectedMapKey);
				}
			}
			return {nodes};
		}
		return {};
	}
}