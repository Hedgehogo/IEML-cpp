#pragma once
#include "../scalar/ScalarNodeData.hpp"

namespace ieml {
	class NullNodeData : public ScalarNodeData {
	public:
		NullNodeData(std::string string);
		
		NodeType getNodeType() override;
	};
}
