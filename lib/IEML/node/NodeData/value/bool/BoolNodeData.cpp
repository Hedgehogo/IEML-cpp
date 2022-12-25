#include "BoolNodeData.hpp"
#include "../exception/NotRequestedTypeException.hpp"

namespace ieml {
	BoolNodeData::BoolNodeData(std::string string, bool value) : ValueNodeData(string), value(value) {}
	
	NodeType BoolNodeData::getNodeType() {
		return NodeType::Bool;
	}
	
	bool BoolNodeData::getBool() {
		return value;
	}
}