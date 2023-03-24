#include "../Parser.hpp"
#include "../../helpers/emptyLines/emptyLines.hpp"
#include "../../helpers/match/match.hpp"
#include "../../exceptions/FailedParseException/FailedParseException.hpp"

namespace ieml {
	static constexpr auto reListSpecial = ctll::fixed_string{R"(-[ \n])"};
	
	bool findListSpecial(String::const_iterator& pos, String::const_iterator end, Mark& mark) {
		bool find{matchAndMove<reListSpecial>(pos, end, mark)};
		if(*(pos - 1) == '\n') {
			--pos;
			--mark.symbol;
		}
		return find;
	}
	
	Option<ListData> Parser::parseList(Size indent) {
		if(ctre::starts_with<reListSpecial>(pos_, end())) {
			ListData nodes{};
			Mark mark{mark_};
			Size currentIndent{indent};
			String::const_iterator pos{pos_};
			while(currentIndent == indent) {
				if(findListSpecial(pos, end(), mark)) {
					pos_ = pos;
					mark_ = mark;
					
					NodeData nodeData{parseTag(indent, false)};
					nodes.emplace_back(std::move(Node{nodeData, mark}));
					
					pos = pos_;
					mark = mark_;
					
					if(pos_ != end() && *pos_ != '\n')
						throw FailedParseException{filePath_, FailedParseException::Reason::ExpectedListItem, mark_};
					skipBlankLines(pos, end(), mark);
					currentIndent = matchAndMove<reTabs>(pos, end(), mark).size();
				} else if(pos == end()) {
					break;
				} else {
					throw FailedParseException{filePath_, FailedParseException::Reason::ExpectedListItem, mark_};
				}
			}
			if(currentIndent > indent)
				throw FailedParseException{filePath_, FailedParseException::Reason::ExpectedListItem, mark_};
			return nodes;
		}
		return {};
	}
}