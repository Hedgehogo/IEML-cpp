#include "../Parser.hpp"
#include "../../helpers/match/match.hpp"
#include "../../helpers/blankLines/blankLines.hpp"

namespace ieml {
	static constexpr auto reTakeAnchor = ctll::fixed_string{R"(&[^\"\n<> ]*)"};
	static constexpr auto reGetAnchor = ctll::fixed_string{R"(\*[^\"\n<> ]*)"};
	
	Option<TakeAnchorData> Parser::parseTakeAnchor(Size indent) {
		if(auto find{matchAndMove<reTakeAnchor>(pos_, end(), mark_)}; find) {
			String name{find.begin() + 1, find.end()};
			if(pos_ != end() && *pos_ == ' ')
				++pos_;
			if(!anchorKeeper_->add(name, parseNode(indent)))
				throw FailedParseException{filePath_, FailedParseException::Reason::AnchorAlreadyExists, mark_};
			return TakeAnchorData{anchorKeeper_, name};
		}
		return {};
	}
	
	Option<GetAnchorData> Parser::parseGetAnchor(Size indent) {
		if(auto find{matchAndMove<reGetAnchor>(pos_, end(), mark_)}; find) {
			String name{find.begin() + 1, find.end()};
			
			skipBlankLine(pos_, end(), mark_);
			return GetAnchorData{anchorKeeper_, name};
		}
		return {};
	}
	
	NodeData Parser::parseAnchor(Size indent) {
		if(auto takeAnchor{parseTakeAnchor(indent)}) {
			return takeAnchor.value();
		}
		if(auto getAnchor{parseGetAnchor(indent)}) {
			return getAnchor.value();
		}
		return parseNode(indent);
	}
}