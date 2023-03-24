#include "Parser.hpp"
#include "../preprocess/preprocess.hpp"

namespace ieml {
	Parser::Parser(const String& inputStr, Rc<AnchorKeeper> anchorKeeper, FilePath filePath) :
		inputStr_(preprocess(inputStr)), pos_(inputStr_.cbegin()), mark_(), anchorKeeper_(anchorKeeper), filePath_(filePath) {
	}
	
	Parser::Parser(const String& inputStr, FilePath filePath, Rc<AnchorKeeper> anchorKeeper) :
		inputStr_(preprocess(inputStr)), pos_(inputStr_.cbegin()), mark_(), anchorKeeper_(anchorKeeper), filePath_(filePath) {
	}
	
	String::const_iterator Parser::end() {
		return inputStr_.cend();
	}
	
	NodeData parse(const String& inputStr) {
		Parser parser{inputStr};
		return parser.parse();
	}
}