//included into ../Parser.hpp
#include "../../helpers/match/match.hpp"
#include "../../helpers/blankLines/blankLines.hpp"

namespace ieml {
	static constexpr auto reTakeAnchor = ctll::fixed_string{R"(&([^\"\n<> ]*) ?)"};
	static constexpr auto reGetAnchor = ctll::fixed_string{R"(\*([^\"\n<> ]*) ?)"};
	
	template<typename Char_, typename FileInclude_>
	Option<BasicTakeAnchorData<Char_>> BasicParser<Char_, FileInclude_>::parseTakeAnchor(Size indent) {
		Mark mark{mark_};
		if(auto find{matchAndMove<reTakeAnchor, Char_>(pos_, end(), mark_)}) {
			BasicString<Char_> name{find.template get<1>().str()};
			if(!anchorKeeper_->add(name, BasicNode<Char_>{parseNode(indent), mark}))
				throw FailedParseException{filePath_, FailedParseException::Reason::AnchorAlreadyExists, mark};
			return {BasicTakeAnchorData<Char_>{anchorKeeper_, name}};
		}
		return {};
	}
	
	template<typename Char_, typename FileInclude_>
	Option<BasicGetAnchorData<Char_>> BasicParser<Char_, FileInclude_>::parseGetAnchor(Size indent) {
		if(auto find{matchAndMove<reGetAnchor, Char_>(pos_, end(), mark_)}) {
			BasicString<Char_> name{find.template get<1>().str()};
			
			skipBlankLine<Char_>(pos_, end(), mark_);
			return {BasicGetAnchorData < Char_ > {anchorKeeper_, name}};
		}
		return {};
	}
}