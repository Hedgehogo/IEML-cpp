#include "NodeAnotherTypeException.hpp"

namespace ieml {
	NodeAnotherTypeException::NodeAnotherTypeException(NodeType requestedType, NodeType nodeType) :
	BaseException(std::string("Node of the '") + getNodeTypeString(nodeType) +std::string("' type cannot be converted to a value of the '") +
	getNodeTypeString(requestedType) + std::string("' type.")), requestedType(requestedType), nodeType(nodeType) {}
	
	NodeType NodeAnotherTypeException::getRequestedType() {
		return requestedType;
	}
	
	NodeType NodeAnotherTypeException::getNodeType() {
		return nodeType;
	}
}