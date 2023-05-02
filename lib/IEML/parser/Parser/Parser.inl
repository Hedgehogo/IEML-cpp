//included into Parser.hpp

#include "../helpers/toChar/toChar.hpp"

namespace ieml {
	template<typename Char_, typename FileInclude_>
	BasicParser<Char_, FileInclude_>::BasicParser(const BasicString<Char_>& inputStr, Rc<BasicAnchorKeeper<Char_>> anchorKeeper, FilePath filePath) :
		pos_(inputStr.cbegin()), end_(inputStr.cend()), mark_(), anchorKeeper_(anchorKeeper), filePath_(filePath) {
	}
	
	template<typename Char_, typename FileInclude_>
	BasicParser<Char_, FileInclude_>::BasicParser(const BasicString<Char_>& inputStr, FilePath filePath, Rc<BasicAnchorKeeper<Char_>> anchorKeeper) :
		pos_(inputStr.cbegin()), end_(inputStr.cend()), mark_(), anchorKeeper_(anchorKeeper), filePath_(filePath) {
	}
	
	template<typename Char_, typename FileInclude_>
	BasicStringCIter<Char_> BasicParser<Char_, FileInclude_>::end() {
		return end_;
	}
	
	template<typename Char_, typename FileInclude_>
	typename BasicParser<Char_, FileInclude_>::PosInfo BasicParser<Char_, FileInclude_>::getPosInfo() {
		return PosInfo{pos_, mark_};
	}
	
	template<typename Char_, typename FileInclude_>
	void BasicParser<Char_, FileInclude_>::setPosInfo(const PosInfo& posInfo) {
		pos_ = posInfo.pos;
		mark_ = posInfo.mark;
	}
	
	template<typename Char_, typename FileInclude_>
	void BasicParser<Char_, FileInclude_>::except(FailedParseException::Reason reason) {
		throw FailedParseException{filePath_, reason, mark_};
	}
	
	template<typename Char_, typename FileInclude_>
	void BasicParser<Char_, FileInclude_>::exceptWithCheckSpace(FailedParseException::Reason reason) {
		if(pos_ != end() && *pos_ == toChar<Char_>(' ')) {
			throw FailedParseException{filePath_, FailedParseException::Reason::ImpermissibleSpace, mark_};
		}
		throw FailedParseException{filePath_, reason, mark_};
	}
}

#include "parse/parse.inl"
#include "parse/parseAnchor.inl"
#include "parse/parseClassicString.inl"
#include "parse/parseFile.inl"
#include "parse/parseList.inl"
#include "parse/parseMap.inl"
#include "parse/parseNode.inl"
#include "parse/parseNotEscapedString.inl"
#include "parse/parseNotScalar.inl"
#include "parse/parseNull.inl"
#include "parse/parseRaw.inl"
#include "parse/parseScalar.inl"
#include "parse/parseShortList.inl"
#include "parse/parseTag.inl"