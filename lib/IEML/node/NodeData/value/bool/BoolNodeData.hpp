#pragma once
#include "../ValueNodeData.hpp"
#include <string>

namespace ieml {
	class BoolNodeData : public ValueNodeData {
	private:
		bool value;
		
	public:
		BoolNodeData(std::string string, bool value);
		
		NodeType getNodeType() override;
		
		bool getBool() override;
	};
}
