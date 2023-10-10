//included into ../Parser.hpp
#include "../../helpers/match/match.hpp"

namespace ieml {
	static constexpr auto re_whitespace = ctll::fixed_string{ R"([\t ]*)"};
	static constexpr auto reSLSeparator = ctll::fixed_string{R"(, )"};
	static constexpr auto reSLRaw = ctll::fixed_string{R"(([^\n\"<>#]|#[^\n\"<>! ])*?#?(?=, |\]))"};
	
	template<typename Char_, typename FileInclude_>
	Option<BasicListData<Char_>> BasicParser<Char_, FileInclude_>::parse_short_list() {
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
					BasicNodeData<Char_> node_data;
					if(auto short_list{parse_short_list()}) {
						node_data = {short_list.some()};
					} else if(auto null{parse_null()}) {
						node_data = {null.some()};
					} else if(auto classic_string{parse_classic_string(0)}) {
						node_data = {classic_string.some()};
					} else if(auto raw{match_and_move<reSLRaw>(pos_, end(), mark_)}) {
						node_data = {RawData{raw.str()}};
					} else {
						except(FailedParseException::Reason::FailedDetermineType);
					}
					
					match_and_move<re_whitespace>(pos_, end(), pos_info.mark);
					if(pos_ != end() && *pos_ == ']') {
						pos_ += 1;
						mark_.symbol += 1;
						nodes.emplace_back(BasicNode{std::move(node_data), pos_info.mark});
						break;
					} else if(match_and_move<reSLSeparator>(pos_, end(), mark_)) {
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