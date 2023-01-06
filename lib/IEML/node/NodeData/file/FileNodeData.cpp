#include "FileNodeData.hpp"
#include "../../Node/Node.hpp"

namespace ieml {
	FileNodeData::FileNodeData(PNodeData nodeData, fs::path filePath) : nodeData(std::move(nodeData)), filePath(filePath) {}
	
	NodeType FileNodeData::getNodeType() const {
		return nodeData->getNodeType();
	}
	
	bool FileNodeData::isFile() const {
		return true;
	}
	
	fs::path FileNodeData::getFilePath() const {
		return filePath;
	}
	
	bool FileNodeData::isWithTag() const {
		return nodeData->isWithTag();
	}
	
	std::string FileNodeData::getTag() const {
		return nodeData->getTag();
	}
	
	std::size_t FileNodeData::getSize() const {
		return nodeData->getSize();
	}
	
	std::string FileNodeData::getString() const {
		return nodeData->getString();
	}
	
	std::vector<Node> FileNodeData::getList() const {
		return nodeData->getList();
	}
	
	std::map<std::string, Node> FileNodeData::getMap() const {
		return nodeData->getMap();
	}
	
	Node &FileNodeData::at(std::size_t index) {
		return nodeData->at(index);
	}
	
	Node &FileNodeData::at(std::string key) {
		return nodeData->at(key);
	}
	
	FileNodeData *FileNodeData::copy() const {
		return new FileNodeData{PNodeData{nodeData->copy()}, filePath};
	}
}