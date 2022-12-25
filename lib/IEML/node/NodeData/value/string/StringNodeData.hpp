#pragma once
#include "../ValueNodeData.hpp"

namespace ieml {
	class StringNodeData : public ValueNodeData {
	public:
		StringNodeData(std::string string);
		
		NodeType getNodeType() override;
	};
}
