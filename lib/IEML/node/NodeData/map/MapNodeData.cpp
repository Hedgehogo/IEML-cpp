#include "MapNodeData.hpp"

namespace ieml {
	MapNodeData::MapNodeData(std::map<std::string, Node> map) : map(std::move(map)) {}
	
	NodeType MapNodeData::getNodeType() {
		return NodeType::Map;
	}
	
	std::size_t MapNodeData::getSize() {
		return map.size();
	}
	
	std::map<std::string, Node> &MapNodeData::getMap() {
		return map;
	}
	
	Node &MapNodeData::at(std::string key) {
		map.at(key);
		return map.at(key);
	}
	
	MapNodeData *MapNodeData::copy() {
		return new MapNodeData{map};
	}
}