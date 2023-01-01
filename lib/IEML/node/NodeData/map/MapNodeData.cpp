#include "MapNodeData.hpp"

namespace ieml {
	MapNodeData::MapNodeData(std::map<std::string, Node> map) : map(std::move(map)) {}
	
	NodeType MapNodeData::getNodeType() {
		return NodeType::Map;
	}
	
	Node &MapNodeData::at(std::string key) {
		map.at(key);
		return map.at(key);
	}
}