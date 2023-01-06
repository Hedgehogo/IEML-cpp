#include "ListNodeData.hpp"

namespace ieml {
	ListNodeData::ListNodeData(std::vector<Node> list) : list(std::move(list)) {}
	
	NodeType ListNodeData::getNodeType() const {
		return NodeType::List;
	}
	
	std::size_t ListNodeData::getSize() const {
		return list.size();
	}
	
	std::vector<Node> ListNodeData::getList() const {
		return list;
	}
	
	Node &ListNodeData::at(std::size_t index) {
		return list.at(index);
	}
	
	ListNodeData *ListNodeData::copy() const {
		return new ListNodeData{list};
	}
}