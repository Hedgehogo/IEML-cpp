#pragma once
#include "../INodeData.hpp"

namespace ieml {
	/// @breef Base class for scalar node data.
	class ScalarNodeData : public INodeData {
	private:
		std::string str;
		
	public:
		ScalarNodeData(std::string str);
		
		NodeType getNodeType() override;
		
		bool isScalar() override;
		
		std::string getString() override;
		
		ScalarNodeData *copy() override;
	};
}
