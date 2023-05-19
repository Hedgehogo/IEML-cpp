#include "NodeAnotherTypeException.hpp"

namespace ieml {
	NodeAnotherTypeException::NodeAnotherTypeException(Mark mark, NodeType requested_type, NodeType node_type) :
		NodeException(mark), requested_type_(requested_type), node_type_(node_type) {
	}
	
	String NodeAnotherTypeException::get_description() const {
		return String("Node of the '") + getStringFromNodeType(node_type_) + String("' type cannot be converted to a value of the '") +
			getStringFromNodeType(requested_type_) + String("' type.");
	}
	
	NodeType NodeAnotherTypeException::get_requested_type() {
		return requested_type_;
	}
	
	NodeType NodeAnotherTypeException::get_node_type() {
		return node_type_;
	}
	
	NodeAnotherTypeException* NodeAnotherTypeException::clone() const {
		return new NodeAnotherTypeException{*this};
	}
}