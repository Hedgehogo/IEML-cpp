#include "FileNodeData.hpp"

namespace ieml {
	FileNodeData::FileNodeData(PNodeData nodeData, fs::path filePath) : nodeData(std::move(nodeData)), filePath(filePath) {}
	
	NodeType FileNodeData::getNodeType() {
		return nodeData->getNodeType();
	}
	
	bool FileNodeData::isFile() {
		return true;
	}
	
	fs::path FileNodeData::getFilePath() {
		return filePath;
	}
	
	bool FileNodeData::isWithTag() {
		return nodeData->isWithTag();
	}
	
	std::string FileNodeData::getTag() {
		return nodeData->getTag();
	}
	
	std::size_t FileNodeData::getSize() {
		return nodeData->getSize();
	}
	
	std::string FileNodeData::getString() {
		return nodeData->getString();
	}
	
	std::map<std::string, Node> &FileNodeData::getMap() {
		return nodeData->getMap();
	}
	
	Node &FileNodeData::at(std::size_t index) {
		return nodeData->at(index);
	}
	
	Node &FileNodeData::at(std::string key) {
		return nodeData->at(key);
	}
	
	FileNodeData *FileNodeData::copy() {
		return new FileNodeData{PNodeData{nodeData->copy()}, filePath};
	}
}