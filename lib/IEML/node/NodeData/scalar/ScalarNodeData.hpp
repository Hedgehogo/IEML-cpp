#pragma once
#include "../INodeData.hpp"

namespace ieml {
	/// @breef Base class for scalar node data.
	class ScalarNodeData : public INodeData {
	private:
		std::string str;
		
	public:
		ScalarNodeData(std::string str);
		
		NodeType getNodeType() const override;
		
		bool isScalar() const override;
		
		std::string getString() const override;
		
		ScalarNodeData *copy() const override;
	};
}
