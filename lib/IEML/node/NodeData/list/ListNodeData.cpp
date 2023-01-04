#include "ListNodeData.hpp"

namespace ieml {
	ListNodeData::ListNodeData(std::vector<Node> list) : list(std::move(list)) {}
	
	NodeType ListNodeData::getNodeType() {
		return NodeType::List;
	}
	
	std::size_t ListNodeData::getSize() {
		return list.size();
	}
	
	Node &ListNodeData::at(std::size_t index) {
		return list.at(index);
	}
}