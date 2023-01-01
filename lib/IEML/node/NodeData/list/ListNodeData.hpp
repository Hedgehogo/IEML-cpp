#pragma once
#include "../INodeData.hpp"
#include "../../Node/Node.hpp"
#include <vector>

namespace ieml {
	class ListNodeData : public INodeData {
	private:
		std::vector<Node> list;
		
	public:
		ListNodeData(std::vector<Node> list);
		
		NodeType getNodeType() override;
		
		Node &at(std::size_t index) override;
	};
}
