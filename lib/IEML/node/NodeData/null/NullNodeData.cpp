#include "NullNodeData.hpp"

namespace ieml {
	NodeType NullNodeData::getNodeType() const {
		return NodeType::Null;
	}
	
	NullNodeData *NullNodeData::copy() const {
		return new NullNodeData{};
	}
}