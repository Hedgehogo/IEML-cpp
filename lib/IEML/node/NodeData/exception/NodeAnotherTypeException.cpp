#include "NodeAnotherTypeException.hpp"

namespace ieml {
	NodeAnotherTypeException::NodeAnotherTypeException(NodeType requestedType, NodeType nodeType) : requestedType(requestedType), nodeType(nodeType) {
	}
	
	std::string NodeAnotherTypeException::getDescription() const {
		return std::string("Node of the '") + getNodeTypeString(nodeType) + std::string("' type cannot be converted to a value of the '") +
			   getNodeTypeString(requestedType) + std::string("' type.");
	}
	
	NodeType NodeAnotherTypeException::getRequestedType() {
		return requestedType;
	}
	
	NodeType NodeAnotherTypeException::getNodeType() {
		return nodeType;
	}
}