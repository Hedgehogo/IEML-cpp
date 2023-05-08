//included into ../Parser.hpp
#include "../../helpers/blankLines/blankLines.hpp"
#include "../../helpers/match/match.hpp"

namespace ieml {
	static constexpr auto reListSpecial = ctll::fixed_string{R"(-( |(?=\n)))"};
	
	template<typename Char_, typename FileInclude_>
	Option<BasicListData<Char_>> BasicParser<Char_, FileInclude_>::parseList(Size indent) {
		if(ctre::starts_with<reListSpecial>(pos_, end())) {
			BasicListData<Char_> nodes{};
			PosInfo posInfo{getPosInfo()};
			bool rightIndent{true};
			while(rightIndent) {
				if(matchAndMove<reListSpecial, Char_>(posInfo.pos, end(), posInfo.mark)) {
					setPosInfo(posInfo);
					BasicNodeData<Char_> nodeData{parseNode(indent + 1)};
					nodes.emplace_back(BasicNode{nodeData, posInfo.mark});
					posInfo = getPosInfo();
					
					if(pos_ != end() && *pos_ != toChar<Char_>('\n'))
						except(FailedParseException::Reason::ExpectedListItem);
					skipBlankLinesLn<Char_>(posInfo.pos, end(), posInfo.mark);
					rightIndent = matchIndent<Char_>(posInfo.pos, end(), posInfo.mark, indent);
				} else if(posInfo.pos == end()) {
					break;
				} else if(*posInfo.pos == toChar<Char_>(' ')) {
					except(FailedParseException::Reason::ImpermissibleSpace);
				} else if(*posInfo.pos == toChar<Char_>('\t')) {
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