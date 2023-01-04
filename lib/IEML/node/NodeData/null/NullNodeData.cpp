#include "NullNodeData.hpp"

namespace ieml {
	NodeType NullNodeData::getNodeType() {
		return NodeType::Null;
	}
	
	NullNodeData *NullNodeData::copy() {
		return new NullNodeData{};
	}
}