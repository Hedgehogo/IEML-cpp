#include "ListNodeData.hpp"

namespace ieml {
	ListNodeData::ListNodeData(std::vector<Node> list) : list(std::move(list)) {}
	
	NodeType ListNodeData::getNodeType() {
		return NodeType::List;
	}
	
	Node &ListNodeData::at(std::size_t index) {
		return list.at(index);
	}
}