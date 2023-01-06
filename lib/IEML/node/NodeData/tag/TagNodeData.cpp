#include <filesystem>
#include "TagNodeData.hpp"
#include "../../Node/Node.hpp"

namespace ieml {
	TagNodeData::TagNodeData(PNodeData nodeData, std::string tag) : nodeData(std::move(nodeData)), tag(tag) {}
	
	NodeType TagNodeData::getNodeType() const {
		return nodeData->getNodeType();
	}
	
	bool TagNodeData::isFile() const {
		return nodeData->isFile();
	}
	
	fs::path TagNodeData::getFilePath() const {
		return nodeData->getFilePath();
	}
	
	bool TagNodeData::isWithTag() const {
		return true;
	}
	
	std::string TagNodeData::getTag() const {
		return tag;
	}
	
	std::size_t TagNodeData::getSize() const {
		return nodeData->getSize();
	}
	
	std::string TagNodeData::getString() const {
		return nodeData->getString();
	}
	
	std::vector<Node> TagNodeData::getList() const {
		return nodeData->getList();
	}
	
	std::map<std::string, Node> TagNodeData::getMap() const {
		return nodeData->getMap();
	}
	
	Node &TagNodeData::at(std::size_t index) {
		return nodeData->at(index);
	}
	
	Node &TagNodeData::at(std::string key) {
		return nodeData->at(key);
	}
	
	TagNodeData *TagNodeData::copy() const {
		return new TagNodeData{PNodeData{nodeData->copy()}, tag};
	}
}