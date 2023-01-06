#pragma once
#include "../INodeData.hpp"

namespace ieml {
	class NullNodeData : public INodeData {
	public:
		NullNodeData() = default;
		
		NodeType getNodeType() const override;
		
		NullNodeData *copy() const override;
	};
}
