#include "MapNodeData.hpp"

namespace ieml {
	MapNodeData::MapNodeData(std::map<std::string, Node> map) : map(std::move(map)) {}
	
	NodeType MapNodeData::getNodeType() const {
		return NodeType::Map;
	}
	
	std::size_t MapNodeData::getSize() const {
		return map.size();
	}
	
	std::map<std::string, Node> MapNodeData::getMap() const {
		return map;
	}
	
	Node &MapNodeData::at(std::string key) {
		if(auto find{map.find(key)}; find != map.end()) {
			return find->second;
		}
		return Node::getUndefined();
	}
	
	MapNodeData *MapNodeData::copy() const {
		return new MapNodeData{map};
	}
}