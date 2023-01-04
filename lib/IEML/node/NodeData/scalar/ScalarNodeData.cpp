#include "ScalarNodeData.hpp"

namespace ieml {
	ScalarNodeData::ScalarNodeData(std::string str) : str(str) {}
	
	NodeType ScalarNodeData::getNodeType() {
		return NodeType::Scalar;
	}
	
	bool ScalarNodeData::isScalar() { return true; }
	
	std::string ScalarNodeData::getString() { return str; }
	
	ScalarNodeData *ScalarNodeData::copy() {
		return new ScalarNodeData{str};
	}
}