#pragma once
#include "../INodeData.hpp"

namespace ieml {
	/// @breef Base class for scalar node data.
	class ScalarNodeData : public INodeData {
	private:
		std::string string;
		
	public:
		ScalarNodeData(std::string string);
		
		NodeType getNodeType() override;
		
		bool isScalar() override;
		
		std::string getString() override;
		
		~ScalarNodeData() = default;
	};
}
