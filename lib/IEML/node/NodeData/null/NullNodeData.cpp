#include "NullNodeData.hpp"

namespace ieml {
	NullNodeData::NullNodeData(std::string string) : ScalarNodeData(string) {}
	
	NodeType NullNodeData::getNodeType() {
		return NodeType::Null;
	}
}