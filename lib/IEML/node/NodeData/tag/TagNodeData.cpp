#include "TagNodeData.hpp"

namespace ieml {
	TagNodeData::TagNodeData(PNodeData nodeData, std::string tag) : nodeData(std::move(nodeData)), tag(tag) {}
	
	NodeType TagNodeData::getNodeType() {
		return nodeData->getNodeType();
	}
	
	bool TagNodeData::isFile() {
		return nodeData->isFile();
	}
	
	std::string TagNodeData::getFilePath() {
		return nodeData->getFilePath();
	}
	
	bool TagNodeData::isWithTag() {
		return true;
	}
	
	std::string TagNodeData::getTag() {
		return tag;
	}
	
	std::size_t TagNodeData::getSize() {
		return nodeData->getSize();
	}
	
	std::string TagNodeData::getString() {
		return nodeData->getString();
	}
	
	std::map<std::string, Node> &TagNodeData::getMap() {
		return nodeData->getMap();
	}
	
	Node &TagNodeData::at(std::size_t index) {
		return nodeData->at(index);
	}
	
	Node &TagNodeData::at(std::string key) {
		return nodeData->at(key);
	}
}