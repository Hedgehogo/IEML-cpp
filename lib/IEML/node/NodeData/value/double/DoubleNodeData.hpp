#pragma once
#include "../ValueNodeData.hpp"

namespace ieml {
	class DoubleNodeData : public ValueNodeData {
	private:
		double value;
		
	public:
		DoubleNodeData(std::string string, double value);
		
		NodeType getNodeType() override;
		
		double getDouble() override;
	};
}
