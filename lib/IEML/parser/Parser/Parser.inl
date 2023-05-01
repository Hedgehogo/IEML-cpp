//included into Parser.hpp

namespace ieml {
	template<typename Char_, typename FileInclude_>
	Parser<Char_, FileInclude_>::Parser(const String& inputStr, Rc<AnchorKeeper> anchorKeeper, FilePath filePath) :
		pos_(inputStr.cbegin()), end_(inputStr.cend()), mark_(), anchorKeeper_(anchorKeeper), filePath_(filePath) {
	}
	
	template<typename Char_, typename FileInclude_>
	Parser<Char_, FileInclude_>::Parser(const String& inputStr, FilePath filePath, Rc<AnchorKeeper> anchorKeeper) :
		pos_(inputStr.cbegin()), end_(inputStr.cend()), mark_(), anchorKeeper_(anchorKeeper), filePath_(filePath) {
	}
	
	template<typename Char_, typename FileInclude_>
	String::const_iterator Parser<Char_, FileInclude_>::end() {
		return end_;
	}
	
	template<typename Char_, typename FileInclude_>
	typename Parser<Char_, FileInclude_>::PosInfo Parser<Char_, FileInclude_>::getPosInfo() {
		return PosInfo{pos_, mark_};
	}
	
	template<typename Char_, typename FileInclude_>
	void Parser<Char_, FileInclude_>::setPosInfo(const PosInfo& posInfo) {
		pos_ = posInfo.pos;
		mark_ = posInfo.mark;
	}
	
	template<typename Char_, typename FileInclude_>
	void Parser<Char_, FileInclude_>::except(FailedParseException::Reason reason) {
		throw FailedParseException{filePath_, reason, mark_};
	}
	
	template<typename Char_, typename FileInclude_>
	void Parser<Char_, FileInclude_>::exceptWithCheckSpace(FailedParseException::Reason reason) {
		if(pos_ != end() && *pos_ == ' ') {
			throw FailedParseException{filePath_, FailedParseException::Reason::ImpermissibleSpace, mark_};
		}
		throw FailedParseException{filePath_, reason, mark_};
	}
}