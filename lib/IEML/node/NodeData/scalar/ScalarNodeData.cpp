#include "ScalarNodeData.hpp"

namespace ieml {
	ScalarNodeData::ScalarNodeData(std::string str) : str(str) {}
	
	NodeType ScalarNodeData::getNodeType() const {
		return NodeType::Scalar;
	}
	
	bool ScalarNodeData::isScalar() const { return true; }
	
	std::string ScalarNodeData::getString() const { return str; }
	
	ScalarNodeData *ScalarNodeData::copy() const {
		return new ScalarNodeData{str};
	}
}