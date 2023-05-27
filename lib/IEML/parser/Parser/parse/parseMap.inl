//included into ../Parser.hpp
#include "../../helpers/blankLines/blankLines.hpp"
#include "../../helpers/match/match.hpp"
#include "../../helpers/tag/tag.hpp"

namespace ieml {
	static constexpr auto reMapKey = ctll::fixed_string{R"(([^\n]*?):( | ?(?=\n)))"};
	
	template<typename Char_, typename FileInclude_>
	Option<BasicMapData<Char_>> BasicParser<Char_, FileInclude_>::parseMap(Size indent) {
		if(ctre::starts_with<reMapKey>(pos_, end())) {
			BasicMapData<Char_> nodes{};
			PosInfo posInfo{getPosInfo()};
			bool rightIndent{true};
			while(rightIndent) {
				if(posInfo.pos == end()) {
					break;
				} else if(*posInfo.pos == toChar<Char_>(' ')) {
					BasicString<Char_> str{posInfo.pos, end()};
					except(FailedParseException::Reason::ImpermissibleSpace);
				} else if(*posInfo.pos == toChar<Char_>('\t')) {
					except(FailedParseException::Reason::ImpermissibleTab);
				} else if(auto find{matchAndMove<reMapKey, Char_>(posInfo.pos, end(), posInfo.mark)}) {
					setPosInfo(posInfo);
					BasicString<Char_> keyStr{find.template get<1>().str()};
					BasicNodeData nodeData{parseNode(indent + 1)};
					nodes.emplace(keyStr, BasicNode<Char_>{nodeData, posInfo.mark});
					posInfo = getPosInfo();
					
					if(pos_ != end() && *pos_ != toChar<Char_>('\n'))
						except(FailedParseException::Reason::ExpectedMapKey);
					skipBlankLinesLn<Char_>(posInfo.pos, end(), posInfo.mark);
					rightIndent = matchIndent<Char_>(posInfo.pos, end(), posInfo.mark, indent);
				} else {
					except(FailedParseException::Reason::ExpectedMapKey);
				}
			}
			return {nodes};
		}
		return {};
	}
}