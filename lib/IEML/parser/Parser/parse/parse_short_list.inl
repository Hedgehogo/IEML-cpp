//included into ../Parser.hpp
#include "../../helpers/match/match.hpp"

namespace ieml {
	static constexpr auto re_whitespace = ctll::fixed_string{R"([\t ]*)"};
	static constexpr auto re_s_l_separator = ctll::fixed_string{R"(, )"};
	static constexpr auto re_s_l_raw = ctll::fixed_string{R"(([^\n\"<>#]|#[^\n\"<>! ])*?#?(?=, |\]))"};
	static constexpr auto re_s_l_get_anchor = ctll::fixed_string{R"(\*([^\n ]+?)(?=, |\]))"};
	
	template<typename Char_, typename FileInclude_>
	Option<BasicListData<Char_> > BasicParser<Char_, FileInclude_>::parse_short_list() {
		if(pos_ != end() && *pos_ == '[') {
			auto pos_info{get_pos_info()};
			auto true_end{end()};
			end_ = std::find(pos_, end(), '\n');
			
			pos_info.pos += 1;
			pos_info.mark.symbol += 1;
			BasicListData<Char_> nodes{};
			if(pos_info.pos != end() && *pos_info.pos == ']') {
				pos_info.pos += 1;
				pos_info.mark.symbol += 1;
				set_pos_info(pos_info);
			} else {
				while(true) {
					set_pos_info(pos_info);
					auto node_data{[this]() -> BasicNodeData<Char_> {
						if(auto get_anchor{match_and_move<re_s_l_get_anchor>(pos_, end(), mark_)}) {
							BasicString<Char_> name{get_anchor.template get<1>().str()};
							return {BasicGetAnchorData<Char_>{anchor_keeper_, std::move(name)}};
						}
						for(auto& short_list: parse_short_list()) {
							return {std::move(short_list)};
						}
						for(auto& null: parse_null()) {
							return {std::move(null)};
						}
						for(auto& classic_string: parse_classic_string(0)) {
							return {std::move(classic_string)};
						}
						if(auto raw{match_and_move<re_s_l_raw>(pos_, end(), mark_)}) {
							return {RawData{raw.str()}};
						}
						except(FailedParseException::Reason::FailedDetermineType);
						return {};
					}()};
					
					match_and_move<re_whitespace>(pos_, end(), pos_info.mark);
					if(pos_ != end() && *pos_ == ']') {
						pos_ += 1;
						mark_.symbol += 1;
						nodes.emplace_back(BasicNode{std::move(node_data), pos_info.mark});
						break;
					} else if(match_and_move<re_s_l_separator>(pos_, end(), mark_)) {
						nodes.emplace_back(BasicNode{std::move(node_data), pos_info.mark});
					} else {
						except(FailedParseException::Reason::ExpectedListItem);
					}
					pos_info = get_pos_info();
				}
			}
			skip_blank_line(pos_, end(), mark_);
			
			end_ = true_end;
			return nodes;
		}
		return {};
	}
}