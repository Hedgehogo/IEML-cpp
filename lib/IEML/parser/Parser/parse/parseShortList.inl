//included into ../Parser.hpp
#include "../../helpers/match/match.hpp"

namespace ieml {
	static constexpr auto reWhitespace = ctll::fixed_string{ R"([\t ]*)"};
	static constexpr auto reSLSeparator = ctll::fixed_string{R"(, )"};
	static constexpr auto reSLRaw = ctll::fixed_string{R"(([^\n\"<>#]|#[^\n\"<>! ])*?#?(?=, |\]))"};
	
	template<typename Char_, typename FileInclude_>
	Option<BasicListData<Char_>> BasicParser<Char_, FileInclude_>::parseShortList() {
		if(pos_ != end() && *pos_ == '[') {
			auto posInfo{getPosInfo()};
			auto trueEnd{end()};
			end_ = std::find(pos_, end(), '\n');
			
			posInfo.pos += 1;
			posInfo.mark.symbol += 1;
			BasicListData<Char_> nodes{};
			if(posInfo.pos != end() && *posInfo.pos == ']') {
				posInfo.pos += 1;
				posInfo.mark.symbol += 1;
				setPosInfo(posInfo);
			} else {
				while(true) {
					setPosInfo(posInfo);
					BasicNodeData<Char_> nodeData;
					if(auto shortList{parseShortList()}) {
						nodeData = {shortList.some()};
					} else if(auto null{parseNull()}) {
						nodeData = {null.some()};
					} else if(auto classicString{parseClassicString(0)}) {
						nodeData = {classicString.some()};
					} else if(auto raw{matchAndMove<reSLRaw>(pos_, end(), mark_)}) {
						nodeData = {RawData{raw.str()}};
					} else {
						except(FailedParseException::Reason::FailedDetermineType);
					}
					
					matchAndMove<reWhitespace>(pos_, end(), posInfo.mark);
					if(pos_ != end() && *pos_ == ']') {
						pos_ += 1;
						mark_.symbol += 1;
						nodes.emplace_back(BasicNode{std::move(nodeData), posInfo.mark});
						break;
					} else if(matchAndMove<reSLSeparator>(pos_, end(), mark_)) {
						nodes.emplace_back(BasicNode{std::move(nodeData), posInfo.mark});
					} else {
						except(FailedParseException::Reason::ExpectedListItem);
					}
					posInfo = getPosInfo();
				}
			}
			skipBlankLine(pos_, end(), mark_);
			
			end_ = trueEnd;
			return nodes;
		}
		return {};
	}
}