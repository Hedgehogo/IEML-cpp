#include "NodeAnotherTypeException.hpp"

namespace ieml {
	NodeAnotherTypeException::NodeAnotherTypeException(NodeType requestedType, NodeType nodeType) : requestedType(requestedType), nodeType(nodeType) {
	}
	
	String NodeAnotherTypeException::getDescription() const {
		return String("Node of the '") + getStringFromNodeType(nodeType) + String("' type cannot be converted to a value of the '") +
			   getStringFromNodeType(requestedType) + String("' type.");
	}
	
	NodeType NodeAnotherTypeException::getRequestedType() {
		return requestedType;
	}
	
	NodeType NodeAnotherTypeException::getNodeType() {
		return nodeType;
	}
}