#include "IntNodeData.hpp"

namespace ieml {
	IntNodeData::IntNodeData(std::string string, llint value) : ValueNodeData(string), value(value) {}
	
	NodeType IntNodeData::getNodeType() {
		return NodeType::Int;
	}
	
	llint IntNodeData::getInt() {
		return value;
	}
}