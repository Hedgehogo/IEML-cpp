#include "ScalarNodeData.hpp"

namespace ieml {
	ScalarNodeData::ScalarNodeData(std::string string) : string(string) {}
	
	NodeType ScalarNodeData::getNodeType() {
		return NodeType::Scalar;
	}
	
	bool ScalarNodeData::isScalar() { return true; }
	
	std::string ScalarNodeData::getString() { return string; }
}