//included into ../Parser.hpp
#include "../../helpers/match/match.hpp"
#include "../../helpers/blankLines/blankLines.hpp"

namespace ieml {
	static constexpr auto reTakeAnchor = ctll::fixed_string{R"(&([^\"\n<> ]*) ?)"};
	static constexpr auto reGetAnchor = ctll::fixed_string{R"(\*([^\"\n<> ]*) ?)"};
	
	template<typename Char_, typename FileInclude_>
	Option<TakeAnchorData> Parser<Char_, FileInclude_>::parseTakeAnchor(Size indent) {
		if(auto find{matchAndMove<reTakeAnchor>(pos_, end(), mark_)}) {
			String name{find.template get<1>().str()};
			if(!anchorKeeper_->add(name, parseNode(indent)))
				throw FailedParseException{filePath_, FailedParseException::Reason::AnchorAlreadyExists, mark_};
			return TakeAnchorData{anchorKeeper_, name};
		}
		return {};
	}
	
	template<typename Char_, typename FileInclude_>
	Option<GetAnchorData> Parser<Char_, FileInclude_>::parseGetAnchor(Size indent) {
		if(auto find{matchAndMove<reGetAnchor>(pos_, end(), mark_)}) {
			String name{find.template get<1>().str()};
			
			skipBlankLine(pos_, end(), mark_);
			return GetAnchorData{anchorKeeper_, name};
		}
		return {};
	}
	
	template<typename Char_, typename FileInclude_>
	Option<NodeData> Parser<Char_, FileInclude_>::parseAnchor(Size indent) {
		if(auto takeAnchor{parseTakeAnchor(indent)}) {
			return takeAnchor.value();
		}
		if(auto getAnchor{parseGetAnchor(indent)}) {
			return getAnchor.value();
		}
		return {};
	}
}