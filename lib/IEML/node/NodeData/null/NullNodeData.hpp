#pragma once
#include "../INodeData.hpp"

namespace ieml {
	class NullNodeData : public INodeData {
	public:
		NullNodeData() = default;
		
		NodeType getNodeType() override;
		
		NullNodeData *copy() override;
	};
}
