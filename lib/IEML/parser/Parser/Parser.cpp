#include "Parser.hpp"

namespace ieml {
	Parser::Parser(const String& inputStr, Rc<AnchorKeeper> anchorKeeper, FilePath filePath) :
		inputStr_(inputStr), pos_(inputStr_.cbegin()), mark_(), anchorKeeper_(anchorKeeper), filePath_(filePath) {
	}
	
	Parser::Parser(const String& inputStr, FilePath filePath, Rc<AnchorKeeper> anchorKeeper) :
		inputStr_(inputStr), pos_(inputStr_.cbegin()), mark_(), anchorKeeper_(anchorKeeper), filePath_(filePath) {
	}
	
	String::const_iterator Parser::end() {
		return inputStr_.cend();
	}
	
	Parser::PosInfo Parser::getPosInfo() {
		return PosInfo{pos_, mark_};
	}
	
	void Parser::setPosInfo(const PosInfo& posInfo) {
		pos_ = posInfo.pos;
		mark_ = posInfo.mark;
	}
	
	void Parser::except(FailedParseException::Reason reason) {
		throw FailedParseException{filePath_, reason, mark_};
	}
	
	void Parser::exceptWithCheckSpace(FailedParseException::Reason reason) {
		if(pos_ != end() && *pos_ == ' ') {
			throw FailedParseException{filePath_, FailedParseException::Reason::ImpermissibleSpace, mark_};
		}
		throw FailedParseException{filePath_, reason, mark_};
	}
}