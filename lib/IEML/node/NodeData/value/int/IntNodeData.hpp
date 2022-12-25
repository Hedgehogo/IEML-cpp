#pragma once
#include "../ValueNodeData.hpp"

namespace ieml {
	class IntNodeData : public ValueNodeData {
	private:
		llint value;
		
	public:
		IntNodeData(std::string string, llint value);
		
		NodeType getNodeType() override;
		
		llint getInt() override;
	};
}
