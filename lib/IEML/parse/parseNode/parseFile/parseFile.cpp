#include "parseFile.hpp"
#include "../../exceptions/FailedParseException.hpp"

namespace ieml {
	INodeData *parseFile(std::string::const_iterator &pos, std::string::const_iterator end, RefKeeper &refKeeper, Mark &mark, size_t indent) {
		throw FailedParseException{{}, mark};
	}
}