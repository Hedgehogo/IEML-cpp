#include "NotRequestedTypeException.hpp"

namespace ieml {
	NotRequestedTypeException::NotRequestedTypeException(std::string type, NodeType nodeType) :
	BaseException(std::string("Node of the '") + getNodeTypeString(nodeType) + std::string("' type cannot be converted to a value of the '") + type + std::string("' type.")) {}
	
	std::string NotRequestedTypeException::getType() {
		return type;
	}
	
	NodeType NotRequestedTypeException::getNodeType() {
		return nodeType;
	}
}