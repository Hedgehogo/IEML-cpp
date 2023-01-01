#include "FileNodeData.hpp"

namespace ieml {
	FileNodeData::FileNodeData(FileNodeData::PNodeData nodeData, std::string filePath) : nodeData(std::move(nodeData)) {}
	
	NodeType FileNodeData::getNodeType() {
		return nodeData->getNodeType();
	}
	
	bool FileNodeData::isFile() {
		return true;
	}
	
	std::string FileNodeData::getFilePath() {
		return filePath;
	}
	
	std::string FileNodeData::getString() {
		return nodeData->getString();
	}
	
	Node &FileNodeData::at(std::size_t index) {
		return nodeData->at(index);
	}
	
	Node &FileNodeData::at(std::string key) {
		return nodeData->at(key);
	}
}