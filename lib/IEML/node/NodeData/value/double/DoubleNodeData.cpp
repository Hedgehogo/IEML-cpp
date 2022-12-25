#include "DoubleNodeData.hpp"

namespace ieml {
	DoubleNodeData::DoubleNodeData(std::string string, double value) : ValueNodeData(string), value(value) {}
	
	NodeType DoubleNodeData::getNodeType() {
		return NodeType::Double;
	}
	
	double DoubleNodeData::getDouble() {
		return value;
	}
}